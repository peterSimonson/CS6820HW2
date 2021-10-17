//
// Created by Peter Simonson on 10/16/21.
//

#ifndef CS6820HW2_NODES_H
#define CS6820HW2_NODES_H

#include <string>

//Super class for all nodes in our tree
class TreeNode {

public:
    virtual std::string NodeToString() = 0;
    virtual int EvaluateNode() = 0;

};

//represents a constant value
class IntegerNode : public TreeNode{
public:
    int value;

    explicit IntegerNode(int valueOfNode);

    int EvaluateNode() override;
    std::string NodeToString() override;
};

//represents a variable value
class VariableNode : public IntegerNode{
public:
    std::string variableName;

    explicit VariableNode(int valueOfVar, std::string const& nameOfVar);
    std::string NodeToString() override;
};

//Interface for our operation classes
class OperationNode : public TreeNode{
public:
    TreeNode * left;
    TreeNode * right;

    OperationNode(TreeNode * leftNode, TreeNode * rightNode);
};

class AddNode : public OperationNode{
public:
    int EvaluateNode() override;
    std::string NodeToString() override;
    //We just need the constructor for Operation Node
    AddNode(TreeNode *leftNode, TreeNode *rightNode) : OperationNode(leftNode, rightNode) {}
};

class SubtractNode : public OperationNode{
public:
    int EvaluateNode() override;
    std::string NodeToString() override;
    //We just need the constructor for Operation Node
    SubtractNode(TreeNode *leftNode, TreeNode *rightNode) : OperationNode(leftNode, rightNode) {}
};

#endif //CS6820HW2_NODES_H
