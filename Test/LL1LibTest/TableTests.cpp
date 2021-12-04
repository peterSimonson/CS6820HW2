//
// Created by Peter Simonson on 10/18/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Table.h"

namespace {

    TEST(TableTests, IsNumTest){
        std::string test = "123";
        ASSERT_TRUE(is_positive_number(test));

        test = "12.3";
        ASSERT_TRUE(is_positive_number(test));

        test = ".3";
        ASSERT_FALSE(is_positive_number(test));

        test = "test";
        ASSERT_FALSE(is_positive_number(test));

        test = ".test";
        ASSERT_FALSE(is_positive_number(test));

        test = "1.2.3";
        ASSERT_FALSE(is_positive_number(test));

        test = ".";
        ASSERT_FALSE(is_positive_number(test));
    }

    TEST(TableTests, IsNameTest){
        std::string test = "123";
        ASSERT_FALSE(is_positive_name(test));

        test = "test";
        ASSERT_TRUE(is_positive_name(test));

        test = "test123";
        ASSERT_TRUE(is_positive_name(test));

        test = "test_123";
        ASSERT_TRUE(is_positive_name(test));

        test = "test___________123";
        ASSERT_TRUE(is_positive_name(test));

        test = "test___________123";
        ASSERT_TRUE(is_positive_name(test));

        test = "123test";
        ASSERT_FALSE(is_positive_name(test));

        test = "123_test";
        ASSERT_FALSE(is_positive_name(test));

        test = "test!";
        ASSERT_FALSE(is_positive_name(test));
    }

    TEST(TableTests, IsTerminalTest){
        //check the terminals
        ASSERT_TRUE(is_terminal(END_TOKEN));
        ASSERT_TRUE(is_terminal(PLUS_TOKEN));
        ASSERT_TRUE(is_terminal(MINUS_TOKEN));
        ASSERT_TRUE(is_terminal(MULTIPLY_TOKEN));
        ASSERT_TRUE(is_terminal(DIVIDE_TOKEN));
        ASSERT_TRUE(is_terminal(OPEN_PAREN_TOKEN));
        ASSERT_TRUE(is_terminal(CLOSE_PAREN_TOKEN));
        ASSERT_TRUE(is_terminal(NAME_TOKEN));
        ASSERT_TRUE(is_terminal(NUM_TOKEN));
        ASSERT_TRUE(is_terminal(EPSILON_TOKEN));

        //check the non-terminals
        ASSERT_FALSE(is_terminal(START_TOKEN));
        ASSERT_FALSE(is_terminal(EXPR_TOKEN));
        ASSERT_FALSE(is_terminal(MULT_DIV_PRIME_TOKEN));
        ASSERT_FALSE(is_terminal(DIV_AND_RIGHT_OP_TOKEN));
    }

    TEST(TableTests, IsFucntionCallTest){

        std::string test = "peter";
        ASSERT_FALSE(is_function_call(test));

        test = "peter(";
        ASSERT_FALSE(is_function_call(test));
        test = "peter)";
        ASSERT_FALSE(is_function_call(test));
        test = "(peter)";
        ASSERT_FALSE(is_function_call(test));
        test = "1peter()";
        ASSERT_FALSE(is_function_call(test));

        test = "peter()";
        ASSERT_TRUE(is_function_call(test));

    }

    TEST(TableTests, RemoveEpsilonTest){
        //remove third element
        std::vector<int> set {NAME_TOKEN, NUM_TOKEN, EPSILON_TOKEN};
        set = removeEpsilonFromSet(set);
        std::vector<int> postRemoveSet{NAME_TOKEN, NUM_TOKEN};
        ASSERT_EQ(set, postRemoveSet);

        //remove second element
        set = {NAME_TOKEN, EPSILON_TOKEN, NUM_TOKEN};
        set = removeEpsilonFromSet(set);
        postRemoveSet = {NAME_TOKEN, NUM_TOKEN};
        ASSERT_EQ(set, postRemoveSet);

        //remove first element
        set = {EPSILON_TOKEN, NAME_TOKEN, NUM_TOKEN};
        set = removeEpsilonFromSet(set);
        postRemoveSet = {NAME_TOKEN, NUM_TOKEN};
        ASSERT_EQ(set, postRemoveSet);

        //remove multiple elements
        set = {EPSILON_TOKEN, EPSILON_TOKEN, NUM_TOKEN};
        set = removeEpsilonFromSet(set);
        postRemoveSet = {NUM_TOKEN};
        ASSERT_EQ(set, postRemoveSet);

        //do not remove an element
        set = {R_TERM_ADD_SUB_TOKEN, NAME_TOKEN, NUM_TOKEN};
        set = removeEpsilonFromSet(set);
        postRemoveSet = {R_TERM_ADD_SUB_TOKEN, NAME_TOKEN, NUM_TOKEN};
        ASSERT_EQ(set, postRemoveSet);
    }

    TEST(TableTests, CheckForEpsilonTest){
        std::vector<int> set {NAME_TOKEN, NUM_TOKEN, EPSILON_TOKEN};
        ASSERT_TRUE(set_contains_epsilon(set));

        set = {NAME_TOKEN, EPSILON_TOKEN, NUM_TOKEN};
        ASSERT_TRUE(set_contains_epsilon(set));

        set = {EPSILON_TOKEN, NAME_TOKEN, NUM_TOKEN};
        ASSERT_TRUE(set_contains_epsilon(set));

        set = {EPSILON_TOKEN, EPSILON_TOKEN, NUM_TOKEN};
        ASSERT_TRUE(set_contains_epsilon(set));

        set = {L_TERM_POWER_TOKEN, NAME_TOKEN, NUM_TOKEN};
        ASSERT_FALSE(set_contains_epsilon(set));
    }

    TEST(TableTests, UnionSetTest){
        std::vector<int> set1 {NAME_TOKEN, NUM_TOKEN, EPSILON_TOKEN};
        std::vector<int> set2 {NAME_TOKEN, NUM_TOKEN, EPSILON_TOKEN};

        //test unionizing identical sets
        set1 = unionize_sets(set1, set2);
        std::sort(set2.begin(), set2.end());
        ASSERT_EQ(set1, set2);

        //test adding factor token
        set2.push_back(L_TERM_MULT_DIV_TOKEN);
        std::sort(set2.begin(), set2.end());
        set1 = unionize_sets(set1, set2);
        ASSERT_EQ(set1, set2);

        set1 = {L_TERM_ADD_SUB_TOKEN, G_FACTOR_TOKEN, EXPR_TOKEN};
        std::vector<int> tempSet = unionize_sets(set1, {EPSILON_TOKEN});
        set1.push_back(EPSILON_TOKEN);
        std::sort(set1.begin(), set1.end());
        ASSERT_EQ(tempSet, set1);
    }

    TEST(TableTests, AddVariableTest){
        Table table = Table();
        ASSERT_EQ(table.variableScopes.size(), 1);

        std::shared_ptr<TreeNode> eight(new IntegerNode(8));
        std::shared_ptr<VariableNode> var1 (new VariableNode(eight, "var1", "num"));

        ASSERT_TRUE(table.AddVariable(var1));
        ASSERT_EQ(table.variableScopes.back().size(), 1);
        ASSERT_FALSE(table.AddVariable(var1));
        ASSERT_EQ(table.variableScopes.back().size(), 1);

        std::shared_ptr<VariableNode> var2 (new VariableNode(eight, "var2", "num"));

        ASSERT_TRUE(table.AddVariable(var2));
        ASSERT_EQ(table.variableScopes.back().size(), 2);
        ASSERT_FALSE(table.AddVariable(var2));
        ASSERT_EQ(table.variableScopes.back().size(), 2);
    }

    TEST(TableTests, GetVariableTest){
        Table table = Table();
        std::string varName = "var1";
        try {
            table.GetVariable(varName);
            FAIL() << "Expected logic error when evaluating";
        }
        catch(std::logic_error const & err) {
            //ensure we have not set the variable to anything
            ASSERT_EQ(table.variableScopes.size(), 1);
        }
        catch(...) {
            FAIL() << "Expected logic error but got a different kind of error";
        }

        std::shared_ptr<TreeNode> eight(new IntegerNode(8));
        std::shared_ptr<VariableNode> var1 (new VariableNode(eight, "var1", "num"));

        table.AddVariable(var1);

        std::shared_ptr<VariableNode> result = table.GetVariable(varName);

        ASSERT_EQ(result->variableName, var1->variableName);
        ASSERT_EQ(result->EvaluateNode(), var1->EvaluateNode());
    }

}