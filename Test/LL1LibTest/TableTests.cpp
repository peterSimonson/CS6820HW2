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

        test = "12.3";
        ASSERT_TRUE(is_number(test));

        test = ".3";
        ASSERT_TRUE(is_number(test));

        test = "test";
        ASSERT_FALSE(is_number(test));

        test = ".test";
        ASSERT_FALSE(is_number(test));

        test = "1.2.3";
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

        //check the non-terminals
        ASSERT_FALSE(is_terminal(START_TOKEN));
        ASSERT_FALSE(is_terminal(EXPR_TOKEN));
        ASSERT_FALSE(is_terminal(EXPR_PRIME_TOKEN));
        ASSERT_FALSE(is_terminal(TERM_TOKEN));
        ASSERT_FALSE(is_terminal(TERM_PRIME_TOKEN));
        ASSERT_FALSE(is_terminal(FACTOR_TOKEN));
    }

    TEST(TableTests, LookUpTableTest){
        Table table;

        //we are going to look up a couple table entries
        int result = table.LookUpTable(END_TOKEN, START_TOKEN);
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