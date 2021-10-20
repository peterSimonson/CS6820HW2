//
// Created by Peter Simonson on 10/18/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Table.h"

namespace {
    TEST(TableTests, TranslateTest){
        std::vector<std::string> words{"(" ,"peter", "+", "12", ")", "*", "2"};

        std::vector<int> tokens =  TranslateWordsToTokens(words);
        std::vector<int> results{END_TOKEN , OPEN_PARAN_TOKEN, NAME_TOKEN, PLUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, MULTIPLY_TOKEN, NUM_TOKEN};
        ASSERT_EQ(tokens, results);

        words = {"(" ,"peter", "-", "12", ")", "/", "2"};
        tokens =  TranslateWordsToTokens(words);
        results = {END_TOKEN , OPEN_PARAN_TOKEN, NAME_TOKEN, MINUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN};
        ASSERT_EQ(tokens, results);
    }

    TEST(TableTests, IsNumTest){
        std::string test = "123";
        ASSERT_TRUE(is_number(test));

        test = "test";
        ASSERT_FALSE(is_number(test));
    }

    TEST(TableTests, IsNameTest){
        std::string test = "123";
        ASSERT_FALSE(is_name(test));

        test = "test";
        ASSERT_TRUE(is_name(test));

        test = "test123";
        ASSERT_TRUE(is_name(test));

        test = "123test";
        ASSERT_FALSE(is_name(test));

        test = "test!";
        ASSERT_FALSE(is_name(test));
    }

    TEST(TableTests, LookUpTableTest){
        Table table;

        //we are going to look up a couple table entries
        int result = table.LookUpTable(END_TOKEN, GOAL_TOKEN);
        ASSERT_EQ(result, ERROR_TOKEN);

        result = table.LookUpTable(END_TOKEN, EXPR_PRIME_TOKEN);
        ASSERT_EQ(result, 4);

        result = table.LookUpTable(END_TOKEN, TERM_PRIME_TOKEN);
        ASSERT_EQ(result, 8);

        result = table.LookUpTable(PLUS_TOKEN, EXPR_PRIME_TOKEN);
        ASSERT_EQ(result, 2);

        result = table.LookUpTable(PLUS_TOKEN, TERM_PRIME_TOKEN);
        ASSERT_EQ(result, 8);

        result = table.LookUpTable(MINUS_TOKEN, EXPR_PRIME_TOKEN);
        ASSERT_EQ(result, 3);

        result = table.LookUpTable(PLUS_TOKEN, TERM_PRIME_TOKEN);
        ASSERT_EQ(result, 8);
    }
}