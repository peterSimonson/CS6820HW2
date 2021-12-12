//
// Created by Peter Simonson on 10/16/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Nodes.h"

namespace {
    TEST(NodeTests, IntegerNodeTests){
        IntegerNode a = IntegerNode(8);

        ASSERT_EQ(a.EvaluateNode(), 8);
        ASSERT_EQ(a.NodeToString(), "8");
    }

    TEST(NodeTests, DecimalNodeTests){
        DecimalNode a = DecimalNode(8.5);

        ASSERT_EQ(a.EvaluateNode(), 8.5);
        ASSERT_EQ(a.NodeToString(), "8.500000");
    }

    TEST(NodeTests, VariableNodeTests){
        std::shared_ptr<TreeNode> a(new DecimalNode(8.5));
        VariableNode var = VariableNode(a, "Test", "ish");

        ASSERT_EQ(var.EvaluateNode(), 8.5);
        ASSERT_EQ(var.NodeToString(), "Test");

        std::shared_ptr<TreeNode>b(new DecimalNode(10.5));
        var.AssignValue(b);

        ASSERT_EQ(var.EvaluateNode(), 10.5);
        ASSERT_EQ(var.NodeToString(), "Test");
    }

    TEST(NodeTests, AddNodeTest){
        //these will be the left and right nodes for our add nodes
        std::shared_ptr<TreeNode> a(new IntegerNode(8));
        std::shared_ptr<TreeNode> var(new VariableNode(a, "Test", "num"));

        AddNode node1 = AddNode(a, var);
        AddNode node2 = AddNode(var, a);
        AddNode node3 = AddNode(a, a);
        AddNode node4 = AddNode(var, var);

        //test NodeToString
        ASSERT_EQ(node1.NodeToString(), "8 + Test");
        ASSERT_EQ(node2.NodeToString(), "Test + 8");
        ASSERT_EQ(node3.NodeToString(), "8 + 8");
        ASSERT_EQ(node4.NodeToString(), "Test + Test");

        //test evaluate node
        ASSERT_EQ(node1.EvaluateNode() , 16);
        ASSERT_EQ(node2.EvaluateNode() , 16);
        ASSERT_EQ(node3.EvaluateNode() , 16);
        ASSERT_EQ(node4.EvaluateNode() , 16);
    }

    TEST(NodeTest, SubtractNodeTest){
        //these will be the left and right nodes for our add nodes
        std::shared_ptr<TreeNode> a(new IntegerNode(8));
        std::shared_ptr<TreeNode> var(new VariableNode(a, "Test", "num"));

        SubtractNode node1 = SubtractNode(a, var);
        SubtractNode node2 = SubtractNode(var, a);
        SubtractNode node3 = SubtractNode(a, a);
        SubtractNode node4 = SubtractNode(var, var);

        //test NodeToString
        ASSERT_EQ(node1.NodeToString(), "8 - Test");
        ASSERT_EQ(node2.NodeToString(), "Test - 8");
        ASSERT_EQ(node3.NodeToString(), "8 - 8");
        ASSERT_EQ(node4.NodeToString(), "Test - Test");

        //test evaluate node
        ASSERT_EQ(node1.EvaluateNode() , 0);
        ASSERT_EQ(node2.EvaluateNode() , 0);
        ASSERT_EQ(node3.EvaluateNode() , 0);
        ASSERT_EQ(node4.EvaluateNode() , 0);
    }

    TEST(NodeTest, DivideNodeTest){
        //these will be the left and right nodes for our add nodes
        std::shared_ptr<TreeNode> a(new IntegerNode(8));
        std::shared_ptr<TreeNode> var(new VariableNode(a, "Test", "num"));

        DivideNode node1 = DivideNode(a, var);
        DivideNode node2 = DivideNode(var, a);
        DivideNode node3 = DivideNode(a, a);
        DivideNode node4 = DivideNode(var, var);

        //test NodeToString
        ASSERT_EQ(node1.NodeToString(), "8 / Test");
        ASSERT_EQ(node2.NodeToString(), "Test / 8");
        ASSERT_EQ(node3.NodeToString(), "8 / 8");
        ASSERT_EQ(node4.NodeToString(), "Test / Test");

        //test evaluate node
        ASSERT_EQ(node1.EvaluateNode() , 1);
        ASSERT_EQ(node2.EvaluateNode() , 1);
        ASSERT_EQ(node3.EvaluateNode() , 1);
        ASSERT_EQ(node4.EvaluateNode() , 1);

        //try to divide by zero
        try {
            std::shared_ptr<TreeNode> zero(new IntegerNode(0));
            DivideNode errorNode = DivideNode(a, zero);
            errorNode.EvaluateNode();

            FAIL() << "Expected runtime error";
        }
        catch(std::logic_error const & err) {
            EXPECT_EQ(err.what(),std::string("Error: Attempted to divide by zero\n"));
        }
        catch(...) {
            FAIL() << "Expected runtime error";
        }
    }

    TEST(NodeTest, UnassignedVariableTest){
        VariableNode variable = VariableNode(nullptr, "test", "ish");

        //try to evaluate an unassigned node
        try {
            variable.EvaluateNode();

            FAIL() << "Expected runtime error when evaluating an unassigned node";
        }
        catch(std::runtime_error const & err) {
            EXPECT_EQ(err.what(),std::string("Error: Attempted to evaluate test before it was defined.\n"));
        }
        catch(...) {
            FAIL() << "Expected runtime error but got a different kind of error";
        }
    }

    TEST(NodeTest, MultiplyNodeTest){
        //these will be the left and right nodes for our add nodes
        std::shared_ptr<TreeNode> a(new IntegerNode(8));
        std::shared_ptr<TreeNode> var(new VariableNode(a, "Test", "num"));

        MultiplyNode node1 = MultiplyNode(a, var);
        MultiplyNode node2 = MultiplyNode(var, a);
        MultiplyNode node3 = MultiplyNode(a, a);
        MultiplyNode node4 = MultiplyNode(var, var);

        //test NodeToString
        ASSERT_EQ(node1.NodeToString(), "8 * Test");
        ASSERT_EQ(node2.NodeToString(), "Test * 8");
        ASSERT_EQ(node3.NodeToString(), "8 * 8");
        ASSERT_EQ(node4.NodeToString(), "Test * Test");

        //test evaluate node
        ASSERT_EQ(node1.EvaluateNode() , 64);
        ASSERT_EQ(node2.EvaluateNode() , 64);
        ASSERT_EQ(node3.EvaluateNode() , 64);
        ASSERT_EQ(node4.EvaluateNode() , 64);
    }

    TEST(NodeTest, NegateNodeTest){
        //these will be the left and right nodes for our add nodes
        std::shared_ptr<TreeNode> a(new IntegerNode(8));
        std::shared_ptr<TreeNode> var(new VariableNode(a, "Test", "num"));

        NegateNode negIntNode = NegateNode(a);
        NegateNode negVarNode = NegateNode(var);

        ASSERT_EQ(negIntNode.EvaluateNode(), -8);
        ASSERT_EQ(negVarNode.EvaluateNode(), -8);
    }

    TEST(NodeTest, ExponentNodeTest){
        //these will be the left and right nodes for our add nodes
        std::shared_ptr<TreeNode> a(new IntegerNode(8));
        std::shared_ptr<TreeNode> var(new VariableNode(a, "Test", "num"));

        auto node1 = ExponentNode(a, var);
        auto node2 = ExponentNode(var, a);
        auto node3 = ExponentNode(a, a);
        auto node4 = ExponentNode(var, var);

        //test NodeToString
        ASSERT_EQ(node1.NodeToString(), "8 ^ Test");
        ASSERT_EQ(node2.NodeToString(), "Test ^ 8");
        ASSERT_EQ(node3.NodeToString(), "8 ^ 8");
        ASSERT_EQ(node4.NodeToString(), "Test ^ Test");

        //test evaluate node
        ASSERT_EQ(node1.EvaluateNode() , 16777216);
        ASSERT_EQ(node2.EvaluateNode() , 16777216);
        ASSERT_EQ(node3.EvaluateNode() , 16777216);
        ASSERT_EQ(node4.EvaluateNode() , 16777216);
    }

    TEST(NodeTest, DecimalOperationTest){
        std::shared_ptr<TreeNode> a(new IntegerNode(8));
        std::shared_ptr<TreeNode> b(new DecimalNode(2.5));

        AddNode add = AddNode(a, b);

        ASSERT_EQ(add.EvaluateNode(), 10.5);
        ASSERT_EQ(add.NodeToString(), "8 + 2.500000");

        SubtractNode sub = SubtractNode(a, b);
        ASSERT_EQ(sub.EvaluateNode(), 5.5);
        ASSERT_EQ(sub.NodeToString(), "8 - 2.500000");

        MultiplyNode multiply = MultiplyNode(a, b);
        ASSERT_EQ(multiply.EvaluateNode(), 20);
        ASSERT_EQ(multiply.NodeToString(), "8 * 2.500000");

        DivideNode divide = DivideNode(a, b);
        ASSERT_EQ(divide.EvaluateNode(), 3.2);
        ASSERT_EQ(divide.NodeToString(), "8 / 2.500000");

        ExponentNode exponent = ExponentNode(a, b);
        ASSERT_EQ(exponent.EvaluateNode(), 181.019335983756166);
        ASSERT_EQ(exponent.NodeToString(), "8 ^ 2.500000");
    }
}