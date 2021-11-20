//
// Created by Peter Simonson on 11/11/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Expression.h"

namespace{
    TEST(ExpressionTests, TranslateTest){
        std::vector<std::string> words{"(" ,"peter", "+", "12", ")", "*", "2"};
        std::vector<std::string> dataTypes = {"ish", "num"};
        auto expr =  TranslateWordsToTokens(words, dataTypes);
        std::vector<int> results{OPEN_PAREN_TOKEN, NAME_TOKEN, PLUS_TOKEN, NUM_TOKEN, CLOSE_PAREN_TOKEN, MULTIPLY_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, words);

        words = {"(" ,"peter", "-", "12", ")", "/", "2"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {OPEN_PAREN_TOKEN, NAME_TOKEN, MINUS_TOKEN, NUM_TOKEN, CLOSE_PAREN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, words);

        words = {"(" ,"peter", "^", "12", ")", "/", "2"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {OPEN_PAREN_TOKEN, NAME_TOKEN, POWER_TOKEN, NUM_TOKEN, CLOSE_PAREN_TOKEN, DIVIDE_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, words);

        words = {"ish", "peter", "=", "2",  "+", "2"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {DATA_TYPE_TOKEN, NAME_TOKEN, EQUALS_TOKEN, NUM_TOKEN, PLUS_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, words);

        words = {"num", "peter", "=", "2",  "+", "2"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {DATA_TYPE_TOKEN, NAME_TOKEN, EQUALS_TOKEN, NUM_TOKEN, PLUS_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, words);

        words = {"num", "num3", "=", "2",  "+", "2"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {DATA_TYPE_TOKEN, NAME_TOKEN, EQUALS_TOKEN, NUM_TOKEN, PLUS_TOKEN, NUM_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, words);

        words = { "num", "result6", "=", "add", "(", "a", ",", "b", ")", " -mult", "(", "a", ",", "b", ")" };
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {DATA_TYPE_TOKEN, NAME_TOKEN, EQUALS_TOKEN, NAME_TOKEN, OPEN_PAREN_TOKEN, NAME_TOKEN, COMMA_TOKEN,
                   NAME_TOKEN, CLOSE_PAREN_TOKEN, MINUS_TOKEN, NAME_TOKEN, OPEN_PAREN_TOKEN, NAME_TOKEN, COMMA_TOKEN,
                   NAME_TOKEN, CLOSE_PAREN_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        words = { "num", "result6", "=", "add", "(", "a", ",", "b", ")", "-", "mult", "(", "a", ",", "b", ")" };
        ASSERT_EQ(expr.words, words);
    }

    TEST(ExpressionTests, TranslateNegativeTest){
        std::vector<std::string> words{"-32", " -", " -32", "-",  "-testVar", "-"," -testVar"};
        std::vector<std::string> dataTypes = {"ish", "num"};

        auto expr =  TranslateWordsToTokens(words, dataTypes);
        std::vector<int> results{NEG_NUM_TOKEN, MINUS_TOKEN ,SPACE_NEG_NUM_TOKEN, MINUS_TOKEN, NEG_NAME_TOKEN, MINUS_TOKEN ,SPACE_NEG_NAME_TOKEN, END_TOKEN};
        std::vector<std::string> text{"-", "32", "-", "-", "32", "-", "-", "testVar", "-", "-", "testVar"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, text);

        words = {"-32", " -32"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {NEG_NUM_TOKEN, MINUS_TOKEN, NUM_TOKEN, END_TOKEN};
        text = {"-", "32", "-", "32"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, text);

        words = {"-test1", " -test2"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        text = {"-", "test1", "-", "test2"};
        results = {NEG_NAME_TOKEN, MINUS_TOKEN, NAME_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, text);
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

        TreeNode * node = evaluatePostFix(postFixExpr);
        int actual = (int) node->EvaluateNode();
        int expected = 1+2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "-"};

        node = evaluatePostFix(postFixExpr);
        actual = (int) node->EvaluateNode();
        expected = 2-2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "*"};

        node = evaluatePostFix(postFixExpr);
        actual = (int) node->EvaluateNode();
        expected = 2*2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "/"};

        node = evaluatePostFix(postFixExpr);
        actual = (int) node->EvaluateNode();
        expected = 2/2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "3", "^"};

        node = evaluatePostFix(postFixExpr);
        actual = (int) node->EvaluateNode();
        expected = 2 * 2 * 2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3", "+", "4", "5", "+", "*"};

        node = evaluatePostFix(postFixExpr);
        actual = (int) node->EvaluateNode();
        expected = (1 + 3) * (4 + 5);

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3", "*", "4", "5", "*", "+"};

        node = evaluatePostFix(postFixExpr);
        actual = (int) node->EvaluateNode();
        expected = 1 * 3 + 4 * 5;

        ASSERT_EQ(actual, expected);
    }

    TEST(ExpressionTests, EvaluatePostFixDecExpressionTest){

        //1+2 in postfix Form
        std::vector<std::string> postFixExpr = {"1.5", "2", "+"};

        TreeNode * node = evaluatePostFix(postFixExpr);
        double actual = node->EvaluateNode();
        double expected = 1.5+2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2.5", "2", "-"};

        node = evaluatePostFix(postFixExpr);
        actual = node->EvaluateNode();
        expected = 2.5-2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2.75", "*"};

        node = evaluatePostFix(postFixExpr);
        actual = node->EvaluateNode();
        expected = 2*2.75;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2.75", "/"};

        node = evaluatePostFix(postFixExpr);
        actual = node->EvaluateNode();
        expected = 2/2.75;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2.5", "3", "^"};

        node = evaluatePostFix(postFixExpr);
        actual = node->EvaluateNode();
        expected = 2.5 * 2.5 * 2.5;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3.6", "+", "4", "5.7", "+", "*"};

        node = evaluatePostFix(postFixExpr);
        actual = node->EvaluateNode();
        expected = (1 + 3.6) * (4 + 5.7);

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1.8", "3", "*", "4.7", "5", "*", "+"};

        node = evaluatePostFix(postFixExpr);
        actual = node->EvaluateNode();
        expected = 1.8 * 3 + 4.7 * 5;

        ASSERT_EQ(actual, expected);
    }
}