//
// Created by Peter Simonson on 10/16/21.
//

#include <cmath>
#include "Nodes.h"

int IntegerNode::EvaluateNode() {
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

int AddNode::EvaluateNode() {
    return left->EvaluateNode() + right->EvaluateNode();
}

std::string AddNode::NodeToString() {
    return left->NodeToString() + " + " + right->NodeToString();
}

int SubtractNode::EvaluateNode() {
    return left->EvaluateNode() - right->EvaluateNode();
}

std::string SubtractNode::NodeToString() {
    return left->NodeToString() + " - " + right->NodeToString();
}

int DivideNode::EvaluateNode() {
    return left->EvaluateNode() / right->EvaluateNode();
}

std::string DivideNode::NodeToString() {
    return left->NodeToString() + " / " + right->NodeToString();
}

int MultiplyNode::EvaluateNode() {
    return left->EvaluateNode() * right->EvaluateNode();
}

std::string MultiplyNode::NodeToString() {
    return left->NodeToString() + " * " + right->NodeToString();
}

std::string ExponentNode::NodeToString() {
    return left->NodeToString() + " ^ " + right->NodeToString();
}

int ExponentNode::EvaluateNode() {
    return pow(left->EvaluateNode(), right->EvaluateNode());
}
