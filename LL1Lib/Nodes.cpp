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

VariableNode::VariableNode(std::shared_ptr<TreeNode> valueOfVar, std::string const &nameOfVar, std::string const &typeOfVar) {
    variableName = nameOfVar;
    variableType = typeOfVar;
    AssignValue(std::move(valueOfVar));
}

std::string VariableNode::NodeToString() {
    return variableName;
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

double SubtractNode::EvaluateNode() {
    return left->EvaluateNode() - right->EvaluateNode();
}

std::string SubtractNode::NodeToString() {
    return left->NodeToString() + " - " + right->NodeToString();
}

double DivideNode::EvaluateNode() {
    double rightNode = right->EvaluateNode();
    if(rightNode!=0){
        return left->EvaluateNode() / rightNode;
    }
    else{
        throw std::runtime_error("Error: Attempted to divide by zero\n");
    }

}

std::string DivideNode::NodeToString() {
    return left->NodeToString() + " / " + right->NodeToString();
}

double MultiplyNode::EvaluateNode() {
    return left->EvaluateNode() * right->EvaluateNode();
}

std::string MultiplyNode::NodeToString() {
    return left->NodeToString() + " * " + right->NodeToString();
}

std::string ExponentNode::NodeToString() {
    return left->NodeToString() + " ^ " + right->NodeToString();
}

double ExponentNode::EvaluateNode() {
    return pow(left->EvaluateNode(), right->EvaluateNode());
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

ProcedureNode::ProcedureNode(std::string name, std::string returnType, std::vector<std::shared_ptr<VariableNode>> parameters) {

    procedureName = std::move(name);
    procedureReturnType = std::move(returnType);
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
    std::string returnVal = procedureName + "(";

    for(int i = 0; i < procedureParameters.size(); i++){
        returnVal += procedureParameters[i]->variableName;

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
