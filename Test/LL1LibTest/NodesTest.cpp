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
        VariableNode var = VariableNode(8, "Test");

        ASSERT_EQ(var.EvaluateNode(), 8);
        ASSERT_EQ(var.NodeToString(), "Test");
    }

    TEST(NodeTests, AddNodeTest){
        //these will be the left and right nodes for our add nodes
        IntegerNode a = IntegerNode(8);
        VariableNode var = VariableNode(8, "Test");

        AddNode node1 = AddNode(&a, &var);
        AddNode node2 = AddNode(&var, &a);
        AddNode node3 = AddNode(&a, &a);
        AddNode node4 = AddNode(&var, &var);

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
        IntegerNode a = IntegerNode(8);
        VariableNode var = VariableNode(8, "Test");

        SubtractNode node1 = SubtractNode(&a, &var);
        SubtractNode node2 = SubtractNode(&var, &a);
        SubtractNode node3 = SubtractNode(&a, &a);
        SubtractNode node4 = SubtractNode(&var, &var);

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
        IntegerNode a = IntegerNode(8);
        VariableNode var = VariableNode(8, "Test");

        DivideNode node1 = DivideNode(&a, &var);
        DivideNode node2 = DivideNode(&var, &a);
        DivideNode node3 = DivideNode(&a, &a);
        DivideNode node4 = DivideNode(&var, &var);

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
    }

    TEST(NodeTest, MultiplyNodeTest){
        //these will be the left and right nodes for our add nodes
        IntegerNode a = IntegerNode(8);
        VariableNode var = VariableNode(8, "Test");

        MultiplyNode node1 = MultiplyNode(&a, &var);
        MultiplyNode node2 = MultiplyNode(&var, &a);
        MultiplyNode node3 = MultiplyNode(&a, &a);
        MultiplyNode node4 = MultiplyNode(&var, &var);

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
        IntegerNode a = IntegerNode(8);
        VariableNode var = VariableNode(12, "Test");

        NegateNode negIntNode = NegateNode(a.EvaluateNode());
        NegateNode negVarNode = NegateNode(var.EvaluateNode());

        ASSERT_EQ(negIntNode.EvaluateNode(), -8);
        ASSERT_EQ(negVarNode.EvaluateNode(), -12);
    }

    TEST(NodeTest, ExponentNodeTest){
        //these will be the left and right nodes for our add nodes
        IntegerNode a = IntegerNode(8);
        VariableNode var = VariableNode(8, "Test");

        auto node1 = ExponentNode(&a, &var);
        auto node2 = ExponentNode(&var, &a);
        auto node3 = ExponentNode(&a, &a);
        auto node4 = ExponentNode(&var, &var);

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
        IntegerNode a = IntegerNode(8);
        DecimalNode b = DecimalNode(2.5);

        AddNode add = AddNode(&a, &b);

        ASSERT_EQ(add.EvaluateNode(), 10.5);
        ASSERT_EQ(add.NodeToString(), "8 + 2.500000");

        SubtractNode sub = SubtractNode(&a, &b);
        ASSERT_EQ(sub.EvaluateNode(), 5.5);
        ASSERT_EQ(sub.NodeToString(), "8 - 2.500000");

        MultiplyNode multiply = MultiplyNode(&a, &b);
        ASSERT_EQ(multiply.EvaluateNode(), 20);
        ASSERT_EQ(multiply.NodeToString(), "8 * 2.500000");

        DivideNode divide = DivideNode(&a, &b);
        ASSERT_EQ(divide.EvaluateNode(), 3.2);
        ASSERT_EQ(divide.NodeToString(), "8 / 2.500000");

        ExponentNode exponent = ExponentNode(&a, &b);
        ASSERT_EQ(exponent.EvaluateNode(), 181.019335983756166);
        ASSERT_EQ(exponent.NodeToString(), "8 ^ 2.500000");
    }
}