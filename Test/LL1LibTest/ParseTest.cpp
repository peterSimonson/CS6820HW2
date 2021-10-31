//
// Created by Peter Simonson on 10/17/21.
//

#include <fstream>
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

    TEST(ParseTests, ParseNegNumTests){
        std::string expr = "-32";
        std::vector<std::string> words = parseWords(expr);
        ASSERT_EQ(words[0], "-32");

        expr = "2 + -32";
        words = parseWords(expr);

        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], " -32");

        expr = "2 - 32";
        words = parseWords(expr);

        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -32");

        expr = "2 - -32";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -");
        ASSERT_EQ(words[2], " -32");

        expr = "2 --32";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -");
        ASSERT_EQ(words[2], "-32");

        expr = "2 ++32";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "+");
        ASSERT_EQ(words[3], "32");

        expr = "2 +-32";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "-32");

        expr = "2 -+32";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -");
        ASSERT_EQ(words[2], "+");
        ASSERT_EQ(words[3], "32");

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

//        std::string expr = "test1 + test2 * test3";
//        std::vector<int> expectedStack{};
//        Table table = Table();
//        Parser parser = Parser(expr, table);
//        //test the initialized stack
//        ASSERT_EQ(parser.stack, expectedStack);
//        //manually add initial stack elements
//        parser.stack.push_back(END_TOKEN);
//        parser.stack.push_back(START_TOKEN);
//
//        //swap out goal
//        parser.SwapStack(0);
//        expectedStack = {END_TOKEN, EXPR_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        //swap out expr
//        parser.SwapStack(1);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        //swap out term
//        parser.SwapStack(5);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, FACTOR_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        //swap out factor
//        parser.SwapStack(11);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, NAME_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        //remove name because it is a match
//        parser.stack.pop_back();
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        //swap out Term prime
//        parser.SwapStack(8);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        //swap out Term Expr prime
//        parser.SwapStack(2);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_TOKEN, PLUS_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        parser.stack.pop_back();
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        parser.SwapStack(5);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, FACTOR_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        parser.SwapStack(11);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, NAME_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        parser.stack.pop_back();
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);
//
//        parser.SwapStack(6);
//        expectedStack = {END_TOKEN, EXPR_PRIME_TOKEN, TERM_PRIME_TOKEN, FACTOR_TOKEN, MULTIPLY_TOKEN};
//        ASSERT_EQ(parser.stack, expectedStack);

    }

    TEST(ParseTest, InvalidParseTest){
        std::ifstream file("../TestResources/BadExpressions.txt");//holds file we are opening
        std::string line; //holds a single expression we wish to parse

        ASSERT_TRUE(file.is_open());

        //generate our table
        Table table = Table();

        //read each line from the file
        while (std::getline(file, line)){
            Parser parse = Parser(line, table);
            //each one of these parses should fail
            ASSERT_FALSE(parse.successfulParse);
        }

        //close input file
        file.close();
    }

    TEST(ParseTest, ValidParseTest){
        std::ifstream file("../TestResources/GoodExpressions.txt");//holds file we are opening
        std::string line; //holds a single expression we wish to parse

        ASSERT_TRUE(file.is_open());

        //generate our table
        Table table = Table();

        //read each line from the file
        while (std::getline(file, line)){
            Parser parse = Parser(line, table);
            //each one of these parses should fail
            ASSERT_TRUE(parse.successfulParse);
        }

        //close input file
        file.close();
    }
}