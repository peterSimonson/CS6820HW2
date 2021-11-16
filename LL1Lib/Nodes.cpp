//
// Created by Peter Simonson on 10/16/21.
//

#include <cmath>
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

VariableNode::VariableNode(int valueOfVar, std::string const& nameOfVar) : IntegerNode{valueOfVar} {
    variableName = nameOfVar;
}

std::string VariableNode::NodeToString() {
    return variableName;
}

OperationNode::OperationNode(TreeNode *leftNode, TreeNode *rightNode) {
    left = leftNode;
    right = rightNode;
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
