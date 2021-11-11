//
// Created by Peter Simonson on 11/11/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Expression.h"

namespace{
    TEST(TableTests, TranslateTest){
        std::vector<std::string> words{"(" ,"peter", "+", "12", ")", "*", "2"};

        auto expr =  TranslateWordsToTokens(words);
        std::vector<int> results{OPEN_PARAN_TOKEN, NAME_TOKEN, PLUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, MULTIPLY_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.text, words);

        words = {"(" ,"peter", "-", "12", ")", "/", "2"};
        expr =  TranslateWordsToTokens(words);
        results = {OPEN_PARAN_TOKEN, NAME_TOKEN, MINUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.text, words);

        words = {"(" ,"peter", "^", "12", ")", "/", "2"};
        expr =  TranslateWordsToTokens(words);
        results = {OPEN_PARAN_TOKEN, NAME_TOKEN, EXPONENT_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.text, words);
    }

    TEST(TableTests, TranslateNegativeTest){
        std::vector<std::string> words{"-32", " -", " -32", "-",  "-testVar", "-"," -testVar"};
        auto expr =  TranslateWordsToTokens(words);
        std::vector<int> results{NEG_NUM_TOKEN, MINUS_TOKEN ,SPACE_NEG_NUM_TOKEN, MINUS_TOKEN, NEG_NAME_TOKEN, MINUS_TOKEN ,SPACE_NEG_NAME_TOKEN, END_TOKEN};
        std::vector<std::string> text{"-", "32", "-", "-", "32", "-", "-", "testVar", "-", "-", "testVar"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.text, text);

        words = {"-32", " -32"};
        expr =  TranslateWordsToTokens(words);
        results = {NEG_NUM_TOKEN, MINUS_TOKEN, NUM_TOKEN, END_TOKEN};
        text = {"-", "32", "-", "32"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.text, text);

        words = {"-test1", " -test2"};
        expr =  TranslateWordsToTokens(words);
        text = {"-", "test1", "-", "test2"};
        results = {NEG_NAME_TOKEN, MINUS_TOKEN, NAME_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.text, text);
    }
}