//
// Created by Peter Simonson on 10/16/21.
//

#include <cmath>
#include <stdexcept>
#include <utility>
#include "Nodes.h"

double IntegerNode::EvaluateNode() {
    return value;
}

std::string IntegerNode::NodeToString() {
    return std::to_string(value);
}

IntegerNode::IntegerNode(int valueOfNode) {
    value = valueOfNode;
}

void IntegerNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    File.SetRegister(std::to_string((int)EvaluateNode()), false, destination, isProcedure);
}

VariableNode::VariableNode(std::shared_ptr<TreeNode> valueOfVar, std::string const &nameOfVar, std::string const &typeOfVar) :
        ObjectNode(nameOfVar, typeOfVar){
    AssignValue(std::move(valueOfVar));
}

std::string VariableNode::NodeToString() {
    return name;
}

void VariableNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    if(isProcedure){
        File.SetRegister(asmRegister, false, destination, isProcedure);
    }
    else{
        File.SetRegister(name, true, destination, isProcedure);
    }
}

OperationNode::OperationNode(std::shared_ptr<TreeNode> leftNode, std::shared_ptr<TreeNode> rightNode) {
    left = std::move(leftNode);
    right = std::move(rightNode);
}

double AddNode::EvaluateNode() {
    return left->EvaluateNode() + right->EvaluateNode();
}

std::string AddNode::NodeToString() {
    return left->NodeToString() + " + " + right->NodeToString();
}

void AddNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    //set the left side to rax
    left->EvaluateToAssembly(File, destination, isProcedure);
    //set the right side to rax
    std::string rhsRegister = "rax";
    right->EvaluateToAssembly(File, rhsRegister, isProcedure);
    File.AddOrSub(destination, "add", rhsRegister, isProcedure);
}

double SubtractNode::EvaluateNode() {
    return left->EvaluateNode() - right->EvaluateNode();
}

std::string SubtractNode::NodeToString() {
    return left->NodeToString() + " - " + right->NodeToString();
}

void SubtractNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    //set the left side to the destination
    left->EvaluateToAssembly(File, destination, isProcedure);
    //set the right side to rax
    std::string rhsRegister = "rax";
    right->EvaluateToAssembly(File, rhsRegister, isProcedure);
    File.AddOrSub(destination, "sub", rhsRegister, isProcedure);
}

double DivideNode::EvaluateNode() {
    double rightNode = right->EvaluateNode();
    if(rightNode!=0){
        return left->EvaluateNode() / rightNode;
    }
    else{
        throw std::logic_error("Error: Attempted to divide by zero\n");
    }

}

std::string DivideNode::NodeToString() {
    return left->NodeToString() + " / " + right->NodeToString();
}

void DivideNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    //set the left side to the destination
    left->EvaluateToAssembly(File, destination, isProcedure);
    //set the right side to rbx
    std::string rhsRegister = "rbx";
    right->EvaluateToAssembly(File, rhsRegister, isProcedure);
    File.MulOrDivVariable(destination, "div", rhsRegister, isProcedure);
}

double MultiplyNode::EvaluateNode() {
    return left->EvaluateNode() * right->EvaluateNode();
}

std::string MultiplyNode::NodeToString() {
    return left->NodeToString() + " * " + right->NodeToString();
}

void MultiplyNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    //set the left side to the destination
    left->EvaluateToAssembly(File, destination, isProcedure);
    //set the right side to rbx
    std::string rhsRegister = "rbx";
    right->EvaluateToAssembly(File, rhsRegister, isProcedure);
    File.MulOrDivVariable(destination, "mul", rhsRegister, isProcedure);
}

std::string ExponentNode::NodeToString() {
    return left->NodeToString() + " ^ " + right->NodeToString();
}

double ExponentNode::EvaluateNode() {
    return pow(left->EvaluateNode(), right->EvaluateNode());
}

void ExponentNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    //set the left side to the destination
    left->EvaluateToAssembly(File, destination, isProcedure);
    //set the right side to rbx
    std::string powerRegister = "rsi";
    right->EvaluateToAssembly(File, powerRegister, isProcedure);
    File.ExponentVariable(powerRegister, destination, isProcedure);
}

DecimalNode::DecimalNode(double valueOfNode) {
    value = valueOfNode;
}

double DecimalNode::EvaluateNode() {
    return value;
}

std::string DecimalNode::NodeToString() {
    return std::to_string(value);
}

void DecimalNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    throw std::runtime_error("Changing ish values in assembly is not implemented");
}

ProcedureNode::ProcedureNode(std::string name, std::string returnType, std::vector<std::shared_ptr<VariableNode>> parametersIn):
        ObjectNode(std::move(name), std::move(returnType)){

    parameters = std::move(parametersIn);
}

void ProcedureNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {

    for(auto & parameter : parameters){
        parameter->operation->EvaluateToAssembly(File, parameter->asmRegister, isProcedure);
    }

    File.WriteProcedureCall(name, isProcedure, destination);

    for(auto & parameter : parameters){
        parameter->operation = nullptr;
    }
}

std::string ProcedureNode::NodeToString() {
    std::string returnVal = name + "(";

    for(int i = 0; i < parameters.size(); i++){
        returnVal += parameters[i]->name;

        if(i + 1 != parameters.size()){
            returnVal += ", ";
        }
    }

    returnVal += ")";

    return returnVal;
}

void ProcedureNode::StartAssemblyDeclaration(AssemblyFile &File) {
    //write the procedure prologue
    File.WriteProcedurePrologue(name);
}

void ProcedureNode::EndAssemblyDeclaration(AssemblyFile &File) {
    //write the procedure. Save the result to rax
    File.SetRegister("rcx", false, "rax", true);

    //write the procedure epilogue
    File.WriteProcedureEpilogue();
    declaredInAsm = true;
}

double ProcedureNode::EvaluateNode() {
    double result = ObjectNode::EvaluateNode();

    for(auto & parameter : parameters){
        parameter->operation = nullptr;
    }
    return result;
}


NegateNode::NegateNode(std::shared_ptr<TreeNode> valueToNegate) {
    value = std::move(valueToNegate);
}

double NegateNode::EvaluateNode() {
    //return the negative of the value you entered into the node
    return -(value->EvaluateNode());
}

std::string NegateNode::NodeToString() {
    return "-" + value->NodeToString();
}

void NegateNode::EvaluateToAssembly(AssemblyFile &File, std::string destination, bool isProcedure) {
    //write the value to assembly
    value->EvaluateToAssembly(File, destination, isProcedure);
    //set the rhs of the multiply to negative 1
    std::string rhsRegister = "rbx";
    File.SetRegister("-1", false, rhsRegister, isProcedure);
    //multiply the value of rcx by negative one to negate it
    File.MulOrDivVariable(destination, "mul", rhsRegister, isProcedure);
}

ObjectNode::ObjectNode(std::string objName, std::string objType) {
    name = std::move(objName);
    type = std::move(objType);
    declaredInAsm = false;
}

void ObjectNode::AssignValue(std::shared_ptr<TreeNode> value) {
    operation = std::move(value);
}

double ObjectNode::EvaluateNode() {
    if(operation != nullptr){
        return operation->EvaluateNode();
    }
    else{
        throw std::runtime_error("Error: Attempted to evaluate " + name + " before it was defined.\n");
    }
}
