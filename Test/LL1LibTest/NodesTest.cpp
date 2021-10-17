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

    TEST(NodeTests, VariableNodeTests){
        VariableNode var = VariableNode(8, "Test");

        ASSERT_EQ(var.EvaluateNode(), 8);
        ASSERT_EQ(var.NodeToString(), "Test");
    }

    TEST(NodeTests, AddNodeTest){
        //these will be the left and right nodes for our add nodes
        IntegerNode a = IntegerNode(8);
        VariableNode var = VariableNode(8, "Test");

        AddNode addNode1 = AddNode(&a, &var);
        AddNode addNode2 = AddNode(&var, &a);
        AddNode addNode3 = AddNode(&a, &a);
        AddNode addNode4 = AddNode(&var, &var);

        //test NodeToString
        ASSERT_EQ(addNode1.NodeToString(), "8 + Test");
        ASSERT_EQ(addNode2.NodeToString(), "Test + 8");
        ASSERT_EQ(addNode3.NodeToString(), "8 + 8");
        ASSERT_EQ(addNode4.NodeToString(), "Test + Test");

        //test evaluate node
        ASSERT_EQ(addNode1.EvaluateNode() , 16);
        ASSERT_EQ(addNode2.EvaluateNode() , 16);
        ASSERT_EQ(addNode3.EvaluateNode() , 16);
        ASSERT_EQ(addNode4.EvaluateNode() , 16);
    }
}