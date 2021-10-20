//
// Created by Peter Simonson on 10/17/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Parse.h"

namespace {

    TEST(ParseTests, ParseConstantsTest){
        std::string expr = "1 + 1";

        std::vector<std::string> words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "1");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "1");
        ASSERT_EQ(words.size(), 3);

        expr = "1+ 1";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "1");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "1");
        ASSERT_EQ(words.size(), 3);

        expr = "1+1";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "1");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "1");
        ASSERT_EQ(words.size(), 3);

        expr = "(1 + 1) * 2";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "(");
        ASSERT_EQ(words[1], "1");
        ASSERT_EQ(words[2], "+");
        ASSERT_EQ(words[3], "1");
        ASSERT_EQ(words[4], ")");
        ASSERT_EQ(words[5], "*");
        ASSERT_EQ(words[6], "2");
        ASSERT_EQ(words.size(), 7);

        expr = "-(1 + 1) * 2";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "-");
        ASSERT_EQ(words[1], "(");
        ASSERT_EQ(words[2], "1");
        ASSERT_EQ(words[3], "+");
        ASSERT_EQ(words[4], "1");
        ASSERT_EQ(words[5], ")");
        ASSERT_EQ(words[6], "*");
        ASSERT_EQ(words[7], "2");
        ASSERT_EQ(words.size(), 8);

        expr = "(1 + 1) / 2";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "(");
        ASSERT_EQ(words[1], "1");
        ASSERT_EQ(words[2], "+");
        ASSERT_EQ(words[3], "1");
        ASSERT_EQ(words[4], ")");
        ASSERT_EQ(words[5], "/");
        ASSERT_EQ(words[6], "2");
        ASSERT_EQ(words.size(), 7);

        expr = "(1 + 1)/2";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "(");
        ASSERT_EQ(words[1], "1");
        ASSERT_EQ(words[2], "+");
        ASSERT_EQ(words[3], "1");
        ASSERT_EQ(words[4], ")");
        ASSERT_EQ(words[5], "/");
        ASSERT_EQ(words[6], "2");
        ASSERT_EQ(words.size(), 7);
    }

    TEST(ParseTests, ParseVaribaleTest){

        std::string expr = "testVar + 1";

        std::vector<std::string> words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "testVar");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "1");
        ASSERT_EQ(words.size(), 3);

        expr = "testVar+ 1";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "testVar");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "1");
        ASSERT_EQ(words.size(), 3);

        expr = "-(1 + testVar) * altVar";
        words = parseWords(expr);
        //Test the words we just parsed
        ASSERT_EQ(words[0], "-");
        ASSERT_EQ(words[1], "(");
        ASSERT_EQ(words[2], "1");
        ASSERT_EQ(words[3], "+");
        ASSERT_EQ(words[4], "testVar");
        ASSERT_EQ(words[5], ")");
        ASSERT_EQ(words[6], "*");
        ASSERT_EQ(words[7], "altVar");
        ASSERT_EQ(words.size(), 8);
    }

    TEST(ParseTest, SwapStack){
        //this test check to see that our swap stack function works with figure 3.13 in the textbook

        std::string expr = "test1 + test2 * test3";
        std::vector<int> expectedStack{END_TOKEN, GOAL_TOKEN};
        Parser parser = Parser(expr);
        //test the initialized stack
        ASSERT_EQ(parser.stack, expectedStack);

        //swap out goal
        parser.SwapStack(0);
        expectedStack = {END_TOKEN, EXPR_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        //swap out expr
        parser.SwapStack(1);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        //swap out term
        parser.SwapStack(5);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, FACTOR_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        //swap out factor
        parser.SwapStack(11);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, NAME_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        //remove name because it is a match
        parser.stack.pop_back();
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        //swap out Term prime
        parser.SwapStack(8);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        //swap out Term Expr prime
        parser.SwapStack(2);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_TOKEN, PLUS_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        parser.stack.pop_back();
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        parser.SwapStack(5);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, FACTOR_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        parser.SwapStack(11);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, NAME_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        parser.stack.pop_back();
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

        parser.SwapStack(6);
        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, FACTOR_TOKEN, MULTIPLY_TOKEN};
        ASSERT_EQ(parser.stack, expectedStack);

    }
}