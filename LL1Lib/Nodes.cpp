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

void IntegerNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    File.SetRegister(std::to_string(EvaluateNode()), false, destination);
}

VariableNode::VariableNode(std::shared_ptr<TreeNode> valueOfVar, std::string const &nameOfVar, std::string const &typeOfVar) :
        ObjectNode(nameOfVar, typeOfVar){
    AssignValue(std::move(valueOfVar));
    //we have not declared this in assembly yet
    declaredInAsm = false;
}

std::string VariableNode::NodeToString() {
    return name;
}

double VariableNode::EvaluateNode() {
    if(valueOfVariable != nullptr){
        return valueOfVariable->EvaluateNode();
    }
    else{
        throw std::runtime_error("Error: Attempted to evaluate unassigned variable\n");
    }

}

void VariableNode::AssignValue(std::shared_ptr<TreeNode> valueOfVar) {
    valueOfVariable = std::move(valueOfVar);
}

void VariableNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    File.SetRegister(name, true, destination);
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

void AddNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    //set the left side to rax
    left->EvaluateToAssembly(File, destination);
    //set the right side to rax
    std::string rhsRegister = "rax";
    right->EvaluateToAssembly(File, rhsRegister);
    File.AddOrSub(destination, "add", rhsRegister);
}

double SubtractNode::EvaluateNode() {
    return left->EvaluateNode() - right->EvaluateNode();
}

std::string SubtractNode::NodeToString() {
    return left->NodeToString() + " - " + right->NodeToString();
}

void SubtractNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    //set the left side to rax
    left->EvaluateToAssembly(File, destination);
    //set the right side to rax
    std::string rhsRegister = "rax";
    right->EvaluateToAssembly(File, rhsRegister);
    File.AddOrSub(destination, "sub", rhsRegister);
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

void DivideNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    throw std::runtime_error("div assembly is not implemented");
}

double MultiplyNode::EvaluateNode() {
    return left->EvaluateNode() * right->EvaluateNode();
}

std::string MultiplyNode::NodeToString() {
    return left->NodeToString() + " * " + right->NodeToString();
}

void MultiplyNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    throw std::runtime_error("mul assembly is not implemented");
}

std::string ExponentNode::NodeToString() {
    return left->NodeToString() + " ^ " + right->NodeToString();
}

double ExponentNode::EvaluateNode() {
    return pow(left->EvaluateNode(), right->EvaluateNode());
}

void ExponentNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    throw std::runtime_error("exponent assembly is not implemented");
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

void DecimalNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    throw std::runtime_error("Changing ish values in assembly is not implemented");
}

ProcedureNode::ProcedureNode(std::string name, std::string returnType, std::vector<std::shared_ptr<VariableNode>> parameters):
        ObjectNode(std::move(name), std::move(returnType)){

    procedureParameters = std::move(parameters);
}

double ProcedureNode::EvaluateNode() {
    if(procedureOperation != nullptr){
        return procedureOperation->EvaluateNode();
    }
    else{
        throw std::runtime_error("Error: Attempted to evaluate undefined procedure\n");
    }
}

std::string ProcedureNode::NodeToString() {
    std::string returnVal = name + "(";

    for(int i = 0; i < procedureParameters.size(); i++){
        returnVal += procedureParameters[i]->name;

        if(i + 1 != procedureParameters.size()){
            returnVal += ", ";
        }
    }

    returnVal += ")";

    return returnVal;
}

void ProcedureNode::AssignValue(std::shared_ptr<TreeNode> valueOfVar) {
    procedureOperation = std::move(valueOfVar);
}

void ProcedureNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    throw std::runtime_error("procedure assembly is not implemented");
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

void NegateNode::EvaluateToAssembly(AssemblyFile &File, std::string destination) {
    //write the value to assembly
    value->EvaluateToAssembly(File, destination);
    //multiply the value of rcx by negative one to negate it
    File.MulOrDivVariable("-1", false, "mul");
}

ObjectNode::ObjectNode(std::string objName, std::string objType) {
    name = std::move(objName);
    type = std::move(objType);
}
