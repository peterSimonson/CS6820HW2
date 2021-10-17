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
}