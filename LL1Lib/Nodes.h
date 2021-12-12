//
// Created by Peter Simonson on 10/16/21.
//

#ifndef CS6820HW2_NODES_H
#define CS6820HW2_NODES_H

#include <string>
#include <utility>
#include <vector>
#include "../AssemblyWriterLib/AssemblyFile.h"

//Super class for all nodes in our tree
class TreeNode {

public:
    virtual std::string NodeToString() = 0;
    virtual double EvaluateNode() = 0;
    virtual void EvaluateToAssembly(AssemblyFile &File, std::string destination) = 0;
    virtual ~TreeNode() = default;

};

//represents a constant integer value
class IntegerNode : public TreeNode{
public:
    int value;

    explicit IntegerNode(int valueOfNode);

    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
};

//represents a constant float value
class DecimalNode : public TreeNode{
public:
    double value;

    explicit DecimalNode(double valueOfNode);

    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
};

//Negate an integer value
class NegateNode : public TreeNode{
public:
    explicit NegateNode(std::shared_ptr<TreeNode> valueToNegate);

    std::shared_ptr<TreeNode>value;

    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
};

class ObjectNode : public TreeNode{
public:
    std::string name;
    std::string type;
    bool declaredInAsm;
    std::shared_ptr<TreeNode> operation = nullptr;
    double EvaluateNode() override;
    void AssignValue(std::shared_ptr<TreeNode> value);
    ObjectNode(std::string objName, std::string objType);
};

//represents a variable value
class VariableNode : public ObjectNode{
public:

    explicit VariableNode(std::shared_ptr<TreeNode> valueOfVar, std::string const &nameOfVar, std::string const &typeOfVar);

    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
};

class ProcedureNode : public ObjectNode{
public:
    //holds the parameters
    std::vector<std::shared_ptr<VariableNode>> procedureParameters;

    explicit ProcedureNode(std::string name, std::string returnType, std::vector<std::shared_ptr<VariableNode>> parameters);
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
};

//Interface for our operation classes
class OperationNode : public TreeNode{
public:
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    OperationNode(std::shared_ptr<TreeNode> leftNode, std::shared_ptr<TreeNode> rightNode);
};

//add two integer values
class AddNode : public OperationNode{
public:
    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
    //We just need the constructor for Operation Node
    AddNode(std::shared_ptr<TreeNode> leftNode, std::shared_ptr<TreeNode> rightNode)
    : OperationNode(std::move(leftNode), std::move(rightNode)) {}
};

//subtract two integer values
class SubtractNode : public OperationNode{
public:
    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
    //We just need the constructor for Operation Node
    SubtractNode(std::shared_ptr<TreeNode> leftNode, std::shared_ptr<TreeNode> rightNode)
    : OperationNode(std::move(leftNode), std::move(rightNode)) {}
};

//Divide two integer values
class DivideNode : public OperationNode{
public:
    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
    //We just need the constructor for Operation Node
    DivideNode(std::shared_ptr<TreeNode> leftNode, std::shared_ptr<TreeNode> rightNode)
    : OperationNode(std::move(leftNode), std::move(rightNode)) {}
};

//multiply two integer values
class MultiplyNode : public OperationNode{
public:
    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
    //We just need the constructor for Operation Node
    MultiplyNode(std::shared_ptr<TreeNode> leftNode, std::shared_ptr<TreeNode> rightNode)
    : OperationNode(std::move(leftNode), std::move(rightNode)) {}
};

//multiply two integer values
class ExponentNode : public OperationNode{
public:
    double EvaluateNode() override;
    void EvaluateToAssembly(AssemblyFile &File, std::string destination) override;
    std::string NodeToString() override;
    //We just need the constructor for Operation Node
    ExponentNode(std::shared_ptr<TreeNode> leftNode, std::shared_ptr<TreeNode> rightNode)
    : OperationNode(std::move(leftNode), std::move(rightNode)) {}
};

#endif //CS6820HW2_NODES_H
