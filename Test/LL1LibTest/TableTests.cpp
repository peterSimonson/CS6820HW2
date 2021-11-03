//
// Created by Peter Simonson on 10/18/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Table.h"

namespace {
    TEST(TableTests, TranslateTest){
        std::vector<std::string> words{"(" ,"peter", "+", "12", ")", "*", "2"};

        std::vector<int> tokens =  TranslateWordsToTokens(words);
        std::vector<int> results{OPEN_PARAN_TOKEN, NAME_TOKEN, PLUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, MULTIPLY_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(tokens, results);

        words = {"(" ,"peter", "-", "12", ")", "/", "2"};
        tokens =  TranslateWordsToTokens(words);
        results = {OPEN_PARAN_TOKEN, NAME_TOKEN, MINUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(tokens, results);
    }

    TEST(TableTests, TranslateNegativeTest){
        std::vector<std::string> words{"-32", " -", " -32", "-",  "-testVar", "-"," -testVar"};
        std::vector<int> tokens =  TranslateWordsToTokens(words);
        std::vector<int> results{NEG_NUM_TOKEN, MINUS_TOKEN ,SPACE_NEG_NUM_TOKEN, MINUS_TOKEN, NEG_NAME_TOKEN, MINUS_TOKEN ,SPACE_NEG_NAME_TOKEN, END_TOKEN};
        ASSERT_EQ(tokens, results);

        words = {"-32", " -32"};
        tokens =  TranslateWordsToTokens(words);
        results = {NEG_NUM_TOKEN, MINUS_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(tokens, results);

        words = {"-test1", " -test2"};
        tokens =  TranslateWordsToTokens(words);
        results = {NEG_NAME_TOKEN, MINUS_TOKEN, NAME_TOKEN, END_TOKEN};
        ASSERT_EQ(tokens, results);
    }

    TEST(TableTests, IsNumTest){
        std::string test = "123";
        ASSERT_TRUE(is_number(test));

        test = "12.3";
        ASSERT_TRUE(is_number(test));

        test = ".3";
        ASSERT_FALSE(is_number(test));

        test = "test";
        ASSERT_FALSE(is_number(test));

        test = ".test";
        ASSERT_FALSE(is_number(test));

        test = "1.2.3";
        ASSERT_FALSE(is_number(test));

        test = ".";
        ASSERT_FALSE(is_number(test));
    }

    TEST(TableTests, IsNameTest){
        std::string test = "123";
        ASSERT_FALSE(is_name(test));

        test = "test";
        ASSERT_TRUE(is_name(test));

        test = "test123";
        ASSERT_TRUE(is_name(test));

        test = "test_123";
        ASSERT_TRUE(is_name(test));

        test = "test___________123";
        ASSERT_TRUE(is_name(test));

        test = "test___________123";
        ASSERT_TRUE(is_name(test));

        test = "123test";
        ASSERT_FALSE(is_name(test));

        test = "123_test";
        ASSERT_FALSE(is_name(test));

        test = "test!";
        ASSERT_FALSE(is_name(test));
    }

    TEST(TableTests, IsTerminalTest){
        //check the terminals
        ASSERT_TRUE(is_terminal(END_TOKEN));
        ASSERT_TRUE(is_terminal(PLUS_TOKEN));
        ASSERT_TRUE(is_terminal(MINUS_TOKEN));
        ASSERT_TRUE(is_terminal(MULTIPLY_TOKEN));
        ASSERT_TRUE(is_terminal(DIVIDE_TOKEN));
        ASSERT_TRUE(is_terminal(OPEN_PARAN_TOKEN));
        ASSERT_TRUE(is_terminal(CLOSE_PARAN_TOKEN));
        ASSERT_TRUE(is_terminal(NAME_TOKEN));
        ASSERT_TRUE(is_terminal(NUM_TOKEN));
        ASSERT_TRUE(is_terminal(EPSILON_TOKEN));

        //check the non-terminals
        ASSERT_FALSE(is_terminal(START_TOKEN));
        ASSERT_FALSE(is_terminal(EXPR_TOKEN));
        ASSERT_FALSE(is_terminal(EXPR_PRIME_TOKEN));
        ASSERT_FALSE(is_terminal(TERM_PRIME_TOKEN));
    }

//    TEST(TableTests, LookUpTableTest){
//
//        Table table = Table();
//
//        //we are going to look up a couple table entries
//        int result = table.LookUpTable(END_TOKEN, START_TOKEN);
//        ASSERT_EQ(result, ERROR_TOKEN);
//
//        result = table.LookUpTable(END_TOKEN, EXPR_PRIME_TOKEN);
//        ASSERT_EQ(result, 4);
//
//        result = table.LookUpTable(END_TOKEN, TERM_PRIME_TOKEN);
//        ASSERT_EQ(result, 8);
//
//        result = table.LookUpTable(PLUS_TOKEN, EXPR_PRIME_TOKEN);
//        ASSERT_EQ(result, 2);
//
//        result = table.LookUpTable(PLUS_TOKEN, TERM_PRIME_TOKEN);
//        ASSERT_EQ(result, 8);
//
//        result = table.LookUpTable(MINUS_TOKEN, EXPR_PRIME_TOKEN);
//        ASSERT_EQ(result, 3);
//
//        result = table.LookUpTable(PLUS_TOKEN, TERM_PRIME_TOKEN);
//        ASSERT_EQ(result, 8);
//    }

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
        set = {R_FACTOR_TOKEN, NAME_TOKEN, NUM_TOKEN};
        set = removeEpsilonFromSet(set);
        postRemoveSet = {R_FACTOR_TOKEN, NAME_TOKEN, NUM_TOKEN};
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

        set = {L_FACTOR_TOKEN, NAME_TOKEN, NUM_TOKEN};
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
        set2.push_back(L_FACTOR_TOKEN);
        std::sort(set2.begin(), set2.end());
        set1 = unionize_sets(set1, set2);
        ASSERT_EQ(set1, set2);

        set1 = {TERM_PRIME_TOKEN, G_FACTOR_TOKEN, EXPR_PRIME_TOKEN};
        std::vector<int> tempSet = unionize_sets(set1, {EPSILON_TOKEN});
        set1.push_back(EPSILON_TOKEN);
        std::sort(set1.begin(), set1.end());
        ASSERT_EQ(tempSet, set1);
    }

    TEST(TableTests, FirstSetTest){
        Table table = Table();

        //start, expr, term and factor should all be the same
        std::vector<int> expectedSet{NEG_NUM_TOKEN, SPACE_NEG_NAME_TOKEN, NAME_TOKEN, NUM_TOKEN, OPEN_PARAN_TOKEN, NEG_NAME_TOKEN, SPACE_NEG_NUM_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[START_TOKEN], expectedSet);
        ASSERT_EQ(table.firstSet[EXPR_TOKEN], expectedSet);
        ASSERT_EQ(table.firstSet[L_TERM_TOKEN], expectedSet);

        expectedSet = {SPACE_NEG_NAME_TOKEN, NAME_TOKEN, NUM_TOKEN, OPEN_PARAN_TOKEN, SPACE_NEG_NUM_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[R_TERM_TOKEN], expectedSet);

        expectedSet = {MINUS_TOKEN, EPSILON_TOKEN, PLUS_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[EXPR_PRIME_TOKEN], expectedSet);

        expectedSet = {DIVIDE_TOKEN, EPSILON_TOKEN, MULTIPLY_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[TERM_PRIME_TOKEN], expectedSet);

        expectedSet = {NEG_NUM_TOKEN, SPACE_NEG_NAME_TOKEN, NAME_TOKEN, NUM_TOKEN, OPEN_PARAN_TOKEN, NEG_NAME_TOKEN, SPACE_NEG_NUM_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[L_FACTOR_TOKEN], expectedSet);

        expectedSet = {SPACE_NEG_NAME_TOKEN, NAME_TOKEN, NUM_TOKEN, OPEN_PARAN_TOKEN, SPACE_NEG_NUM_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[R_FACTOR_TOKEN], expectedSet);
        ASSERT_EQ(table.firstSet[G_FACTOR_TOKEN], expectedSet);

        expectedSet = {NAME_TOKEN, NUM_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[POSVAL_TOKEN], expectedSet);

        expectedSet = {SPACE_NEG_NAME_TOKEN, SPACE_NEG_NUM_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.firstSet[SPACE_NEG_VAL_TOKEN], expectedSet);

        for(int i = NUM_OF_NON_TERMINALS; i <= NUM_OF_TOKENS; i++){
            //the first set entry for a terminal should be the same terminal
            expectedSet = {i};
            ASSERT_EQ(table.firstSet[i], expectedSet);
        }
    }

    TEST(TableTests, FollowSetTest){
        Table table = Table();

        //check that follow set only has non-terminals for entries
        ASSERT_EQ(table.followSet.size(), NUM_OF_NON_TERMINALS);

        //check the entries
        std::vector<int> expectedSet = {END_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.followSet[START_TOKEN], expectedSet);

        expectedSet = {END_TOKEN, CLOSE_PARAN_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.followSet[EXPR_TOKEN], expectedSet);

        expectedSet = {CLOSE_PARAN_TOKEN, MINUS_TOKEN, PLUS_TOKEN, END_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.followSet[L_TERM_TOKEN], expectedSet);

        expectedSet = {CLOSE_PARAN_TOKEN, MINUS_TOKEN, MULTIPLY_TOKEN, PLUS_TOKEN, END_TOKEN, DIVIDE_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.followSet[R_TERM_TOKEN], expectedSet);

        expectedSet = {END_TOKEN, CLOSE_PARAN_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.followSet[EXPR_PRIME_TOKEN], expectedSet);

        expectedSet = {PLUS_TOKEN, CLOSE_PARAN_TOKEN, MINUS_TOKEN, DIVIDE_TOKEN, MULTIPLY_TOKEN, END_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.followSet[TERM_PRIME_TOKEN], expectedSet);

        expectedSet = {CLOSE_PARAN_TOKEN, MINUS_TOKEN, MULTIPLY_TOKEN, PLUS_TOKEN, END_TOKEN, DIVIDE_TOKEN};
        std::sort(expectedSet.begin(), expectedSet.end());
        ASSERT_EQ(table.followSet[L_FACTOR_TOKEN], expectedSet);
        ASSERT_EQ(table.followSet[R_FACTOR_TOKEN], expectedSet);
        ASSERT_EQ(table.followSet[G_FACTOR_TOKEN], expectedSet);
        ASSERT_EQ(table.followSet[POSVAL_TOKEN], expectedSet);
        ASSERT_EQ(table.followSet[SPACE_NEG_VAL_TOKEN], expectedSet);
    }

//    TEST(TableTests, FirstPlusSetTest){
//        Table table = Table();
//
//        //productions 4 and 8 should be different from 1st. Otherwise, first+ should be the same as first
//        for(const std::pair<const int, rule>& productionRule: table.rules){
//
//            rule production = productionRule.second;
//            std::vector<int> expectedSet = table.firstSet[production.rightHandSide.front()];
//            std::vector<int> firstPlusSet = table.findFirstPlusSet(production);
//            if(productionRule.first == 4){
//                expectedSet = {END_TOKEN, CLOSE_PARAN_TOKEN, EPSILON_TOKEN};
//                ASSERT_EQ(expectedSet, firstPlusSet);
//            }
//            else if(productionRule.first == 8){
//                expectedSet = {END_TOKEN, PLUS_TOKEN, MINUS_TOKEN, CLOSE_PARAN_TOKEN, EPSILON_TOKEN};
//                ASSERT_EQ(expectedSet, firstPlusSet);
//            }
//            else{
//                ASSERT_EQ(expectedSet, firstPlusSet);
//            }
//        }
//    }

    TEST(TableTests, TableTest){

        //this is what the table from the text book looks like
        int ExpectedRuleTable [NUM_OF_TOKENS - NUM_OF_NON_TERMINALS][NUM_OF_NON_TERMINALS] = {
                {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 6, 10, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, //Column 1
                {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 4, 10, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, //Column 2
                {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 5, 10, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, //Column 3
                {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 7, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, // 4
                {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 8, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, // 5
                //{ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 9, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, // exponent column
                {0, 1, 2, 3, ERROR_TOKEN, ERROR_TOKEN, 11, 14, 15, ERROR_TOKEN, ERROR_TOKEN}, // Open Paran column
                {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 6, 10, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, // close paran column
                {0, 1, 2, 3, ERROR_TOKEN, ERROR_TOKEN, 11, 14, 16, 19, ERROR_TOKEN}, //name column
                {0, 1, 2, 3, ERROR_TOKEN, ERROR_TOKEN, 11, 14, 16, 18, ERROR_TOKEN}, //num column
                {0, 1, 2, 3, ERROR_TOKEN, ERROR_TOKEN, 11, 14, 17, ERROR_TOKEN, 21}, //space neg name column
                {0, 1, 2, 3, ERROR_TOKEN, ERROR_TOKEN, 11, 14, 17, ERROR_TOKEN, 20}, //space neg num column
                {0, 1, 2, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 13, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN}, //neg name column
                {0, 1, 2, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 12, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN} //neg num column
        };

        //generate the table using our code
        Table table = Table();

        //check that every entry of the table is equal to the textbook's table
        for(int A = START_TOKEN; A < NUM_OF_NON_TERMINALS; A++){
            for(int w = START_TOKEN; w < NUM_OF_TOKENS - NUM_OF_NON_TERMINALS; w++){
                //EXPECT_EQ(table.RuleTable[w][A], ExpectedRuleTable[w][A]);
                std::cout << table.RuleTable[w][A] << "\t";
            }
            std::cout << std::endl;
        }

    }
}