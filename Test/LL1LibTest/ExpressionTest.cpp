//
// Created by Peter Simonson on 11/11/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Expression.h"

namespace{
    TEST(ExpressionTests, TranslateTest){
        std::vector<std::string> words{"(" ,"peter", "+", "12", ")", "*", "2"};

        auto expr =  TranslateWordsToTokens(words);
        std::vector<int> results{OPEN_PARAN_TOKEN, NAME_TOKEN, PLUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, MULTIPLY_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.infix, words);

        words = {"(" ,"peter", "-", "12", ")", "/", "2"};
        expr =  TranslateWordsToTokens(words);
        results = {OPEN_PARAN_TOKEN, NAME_TOKEN, MINUS_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.infix, words);

        words = {"(" ,"peter", "^", "12", ")", "/", "2"};
        expr =  TranslateWordsToTokens(words);
        results = {OPEN_PARAN_TOKEN, NAME_TOKEN, EXPONENT_TOKEN, NUM_TOKEN, CLOSE_PARAN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.infix, words);
    }

    TEST(ExpressionTests, TranslateNegativeTest){
        std::vector<std::string> words{"-32", " -", " -32", "-",  "-testVar", "-"," -testVar"};
        auto expr =  TranslateWordsToTokens(words);
        std::vector<int> results{NEG_NUM_TOKEN, MINUS_TOKEN ,SPACE_NEG_NUM_TOKEN, MINUS_TOKEN, NEG_NAME_TOKEN, MINUS_TOKEN ,SPACE_NEG_NAME_TOKEN, END_TOKEN};
        std::vector<std::string> text{"-", "32", "-", "-", "32", "-", "-", "testVar", "-", "-", "testVar"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.infix, text);

        words = {"-32", " -32"};
        expr =  TranslateWordsToTokens(words);
        results = {NEG_NUM_TOKEN, MINUS_TOKEN, NUM_TOKEN, END_TOKEN};
        text = {"-", "32", "-", "32"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.infix, text);

        words = {"-test1", " -test2"};
        expr =  TranslateWordsToTokens(words);
        text = {"-", "test1", "-", "test2"};
        results = {NEG_NAME_TOKEN, MINUS_TOKEN, NAME_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.infix, text);
    }

    TEST(ExpressionTests, ConvertToPostFixTest){

        //a+b*(c^d-e)^(f+g*h)-i
        std::vector<std::string> text = {"a", "+", "b", "*", "(", "c", "^", "d", "-", "e", ")", "^", "(", "f", "+", "g", "*", "h", ")", "-", "i"};
        std::vector<std::string> actual = convertTextToPostFix(text);
        std::vector<std::string> expected = {"a", "b", "c", "d", "^", "e", "-", "f", "g", "h", "*", "+", "^", "*", "+", "i", "-"};

        ASSERT_EQ(actual, expected);

        //"x^y/(5*z)+2"
        text = {"x", "^", "y", "/", "(", "5", "*", "z", ")", "+", "2"};
        actual = convertTextToPostFix(text);
        expected = {"x", "y", "^", "5", "z", "*", "/", "2", "+"};

        ASSERT_EQ(actual, expected);

        text = {
            "1", "+", "2", "*", "(", "2", "^", "4", "-", "5",
            ")", "^", "(", "1", "+", "2", "*", "3", ")", "-", "9"};
        actual = convertTextToPostFix(text);
        expected = {"1", "2", "2", "4", "^", "5", "-", "1", "2", "3", "*", "+", "^", "*", "+", "9", "-"};

        ASSERT_EQ(actual, expected);

        text = {"(", "A", "+", "B", ")", "*", "(", "C", "+", "D", ")"};
        actual = convertTextToPostFix(text);
        expected = {"A", "B", "+", "C", "D", "+", "*"};

        ASSERT_EQ(actual, expected);

        text = {"A", "*", "B", "+", "C", "*", "D"};
        actual = convertTextToPostFix(text);
        expected = {"A", "B", "*", "C", "D", "*", "+"};

        ASSERT_EQ(actual, expected);
    }

    TEST(ExpressionTests, EvaluatePostFixIntExpressionTest){
        //1+2 in postfix Form
        std::vector<std::string> postFixExpr = {"1", "2", "+"};

        int actual = evaluatePostFixExpression(postFixExpr);
        int expected = 1+2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "-"};

        actual = evaluatePostFixExpression(postFixExpr);
        expected = 2-2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "*"};

        actual = evaluatePostFixExpression(postFixExpr);
        expected = 2*2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "/"};

        actual = evaluatePostFixExpression(postFixExpr);
        expected = 2/2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "3", "^"};

        actual = evaluatePostFixExpression(postFixExpr);
        expected = 2 * 2 * 2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3", "+", "4", "5", "+", "*"};

        actual = evaluatePostFixExpression(postFixExpr);
        expected = (1 + 3) * (4 + 5);

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3", "*", "4", "5", "*", "+"};

        actual = evaluatePostFixExpression(postFixExpr);
        expected = 1 * 3 + 4 * 5;

        ASSERT_EQ(actual, expected);
    }
}