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
        std::vector<std::string> text{"-32", "-", "-32", "-",  "-testVar", "-", "-testVar"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, text);

        words = {"-32", " -32"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        results = {NEG_NUM_TOKEN, MINUS_TOKEN, NUM_TOKEN, END_TOKEN};
        text = {"-32", "-", "32"};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, text);

        words = {"-test1", " -test2"};
        expr =  TranslateWordsToTokens(words, dataTypes);
        text = {"-test1", "-", "test2"};
        results = {NEG_NAME_TOKEN, MINUS_TOKEN, NAME_TOKEN, END_TOKEN};
        ASSERT_EQ(expr.tokens, results);
        ASSERT_EQ(expr.words, text);
    }

    TEST(ExpressionTests, ConvertToPostFixTest){

        //a+b*(c^d-e)^(f+g*h)-i
        std::vector<std::string> text = {"a", "+", "b", "*", "(", "c", "^", "d", "-", "e", ")", "^", "(", "f", "+", "g", "*", "h", ")", "-", "i"};
        std::vector<std::string> actual = convertInfixToPostFix(text);
        std::vector<std::string> expected = {"a", "b", "c", "d", "^", "e", "-", "f", "g", "h", "*", "+", "^", "*", "+", "i", "-"};

        ASSERT_EQ(actual, expected);

        //"x^y/(5*z)+2"
        text = {"x", "^", "y", "/", "(", "5", "*", "z", ")", "+", "2"};
        actual = convertInfixToPostFix(text);
        expected = {"x", "y", "^", "5", "z", "*", "/", "2", "+"};

        ASSERT_EQ(actual, expected);

        text = {
            "1", "+", "2", "*", "(", "2", "^", "4", "-", "5",
            ")", "^", "(", "1", "+", "2", "*", "3", ")", "-", "9"};
        actual = convertInfixToPostFix(text);
        expected = {"1", "2", "2", "4", "^", "5", "-", "1", "2", "3", "*", "+", "^", "*", "+", "9", "-"};

        ASSERT_EQ(actual, expected);

        text = {"(", "A", "+", "B", ")", "*", "(", "C", "+", "D", ")"};
        actual = convertInfixToPostFix(text);
        expected = {"A", "B", "+", "C", "D", "+", "*"};

        ASSERT_EQ(actual, expected);

        text = {"A", "*", "B", "+", "C", "*", "D"};
        actual = convertInfixToPostFix(text);
        expected = {"A", "B", "*", "C", "D", "*", "+"};

        ASSERT_EQ(actual, expected);
    }

    TEST(ExpressionTests, ConvertProcedureCallsPostFixTest){
        std::vector<std::string> text = {"add", "(", "a", ",", "b", ")","*", "B", "+", "C", "*", "D"};
        std::vector<std::string> actual = convertInfixToPostFix(text);
        std::vector<std::string> expected = {"add(a,b)", "B", "*", "C", "D", "*", "+"};

        ASSERT_EQ(actual, expected);

        text = {"(", "sub", "(", "abba", ",", "paulsimon", ")", "+", "B", ")", "*", "(", "add", "(", "a", ",", "b", ")", "+", "D", ")"};
        actual = convertInfixToPostFix(text);
        expected = {"sub(abba,paulsimon)", "B", "+", "add(a,b)", "D", "+", "*"};

        ASSERT_EQ(actual, expected);
    }

    TEST(ExpressionTests, EvaluatePostFixIntExpressionTest){
        //1+2 in postfix Form
        std::vector<std::string> postFixExpr = {"1", "2", "+"};

        std::shared_ptr<TreeNode> node = evaluatePostFix(postFixExpr, Table());
        int actual = (int) node->EvaluateNode();
        int expected = 1+2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "-"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = (int) node->EvaluateNode();
        expected = 2-2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "*"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = (int) node->EvaluateNode();
        expected = 2*2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2", "/"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = (int) node->EvaluateNode();
        expected = 2/2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "3", "^"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = (int) node->EvaluateNode();
        expected = 2 * 2 * 2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3", "+", "4", "5", "+", "*"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = (int) node->EvaluateNode();
        expected = (1 + 3) * (4 + 5);

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3", "*", "4", "5", "*", "+"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = (int) node->EvaluateNode();
        expected = 1 * 3 + 4 * 5;

        ASSERT_EQ(actual, expected);
    }

    TEST(ExpressionTests, EvaluatePostFixDecExpressionTest){

        //1+2 in postfix Form
        std::vector<std::string> postFixExpr = {"1.5", "2", "+"};

        std::shared_ptr<TreeNode> node = evaluatePostFix(postFixExpr, Table());
        double actual = node->EvaluateNode();
        double expected = 1.5+2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2.5", "2", "-"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = node->EvaluateNode();
        expected = 2.5-2;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2.75", "*"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = node->EvaluateNode();
        expected = 2*2.75;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2", "2.75", "/"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = node->EvaluateNode();
        expected = 2/2.75;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"2.5", "3", "^"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = node->EvaluateNode();
        expected = 2.5 * 2.5 * 2.5;

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1", "3.6", "+", "4", "5.7", "+", "*"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = node->EvaluateNode();
        expected = (1 + 3.6) * (4 + 5.7);

        ASSERT_EQ(actual, expected);

        postFixExpr = {"1.8", "3", "*", "4.7", "5", "*", "+"};

        node = evaluatePostFix(postFixExpr, Table());
        actual = node->EvaluateNode();
        expected = 1.8 * 3 + 4.7 * 5;

        ASSERT_EQ(actual, expected);
    }

    TEST(ExpressionTests, EvaluateExpressionTest){
        Table table = Table();

        std::vector<std::string> line = {"num", "var1"};
        Expression expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        ASSERT_EQ(table.variableScopes.back().size(), 1);
        ASSERT_EQ(table.variableScopes.back().back()->variableName, "var1");
        ASSERT_EQ(table.variableScopes.back().back()->variableType, "num");

        line = {"var1", "=", "42"};
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        ASSERT_EQ(table.variableScopes.back().size(), 1);
        ASSERT_EQ(table.variableScopes.back().back()->variableName, "var1");
        ASSERT_EQ(table.variableScopes.back().back()->variableType, "num");
        ASSERT_EQ(table.variableScopes.back().back()->EvaluateNode(), 42);

        line = {"ish", "var2", "=", "42.5"};
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        ASSERT_EQ(table.variableScopes.back().size(), 2);
        ASSERT_EQ(table.variableScopes.back().back()->variableName, "var2");
        ASSERT_EQ(table.variableScopes.back().back()->variableType, "ish");
        ASSERT_EQ(table.variableScopes.back().back()->EvaluateNode(), 42.5);

        line = {"ish", "var3", "=", "var2", "+", "var2"};
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);
        ASSERT_EQ(table.variableScopes.back().size(), 3);
        ASSERT_EQ(table.variableScopes.back().back()->variableName, "var3");
        ASSERT_EQ(table.variableScopes.back().back()->variableType, "ish");
        ASSERT_EQ(table.variableScopes.back().back()->EvaluateNode(), 85);

    }

    TEST(ExpressionTests, EvaluateProceduresTest){
        Table table = Table();

        std::vector<std::string> line = {"num", "procedure", "add", "(", "num", "a", ",", "num", "b", ")", "{"} ;
        Expression expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        //2 variable scopes
        ASSERT_EQ(table.variableScopes.size(), 2);
        //two variables in the current scope
        ASSERT_EQ(table.variableScopes.back().size(), 2);
        //1 procedure declared
        ASSERT_EQ(table.procedures.size(), 1);

        ProcedureNode declaredProcedure = table.procedures.back();
        ASSERT_EQ(declaredProcedure.procedureName, "add");
        ASSERT_EQ(declaredProcedure.procedureParameters.size(), 2);

        //line in the procedure
        line = {"num", "result", "=", "a", "+", "b"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        ASSERT_EQ(table.variableScopes.size(), 2);
        //two variables in the current scope
        ASSERT_EQ(table.variableScopes.back().size(), 3);

        //return statement in the procedure
        line = {"return", "result"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);
        //We should have a return operation now
        ASSERT_NE(table.procedures.back().procedureOperation, nullptr);

        //end the procedure
        line = {"}"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        //1 variable scope
        ASSERT_EQ(table.variableScopes.size(), 1);
        //zero variables in the current scope
        ASSERT_EQ(table.variableScopes.back().size(), 0);
    }

    TEST(ExpressionTests, AssignmentWithProceduresTest){
        Table table = Table();

        std::vector<std::string> line = {"num", "procedure", "add", "(", "num", "a", ",", "num", "b", ")", "{"} ;
        Expression expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        line = {"num", "result", "=", "a", "+", "b"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        //return statement in the procedure
        line = {"return", "result"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        //end the procedure
        line = {"}"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        line = {"num", "var1", "=", "add", "(", "1", ",",  "1", ")"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        ASSERT_EQ(2, table.variableScopes.back().back()->EvaluateNode());

        line = {"num", "var2", "=", "add", "(", "var1", ",",  "1", ")"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        ASSERT_EQ(3, table.variableScopes.back().back()->EvaluateNode());
    }

    TEST(ExpressionTests, ProcedureOverloadingTest){
        Table table = Table();

        std::vector<std::string> line = {"num", "procedure", "add", "(", "num", "a", ",", "num", "b", ")", "{"} ;
        Expression expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);

        //1 procedure declared
        ASSERT_EQ(table.procedures.size(), 1);

        line = {"num", "procedure", "add", "(", "num", "a", ",", "num", "b", ")", "{"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        //try to declare a procedure we already have
        try {
            expr.EvaluateExpression(table);
            FAIL() << "Expected logic error when evaluating";
        }
        catch(std::logic_error const & err) {
            ASSERT_EQ(table.procedures.size(), 1);
        }
        catch(...) {
            FAIL() << "Expected logic error but got a different kind of error";
        }
        //overload for add
        line = {"num", "procedure", "add", "(", "num", "a", ",", "num", "b", "num", "c", ")", "{"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);
        //2 procedure declared
        ASSERT_EQ(table.procedures.size(), 2);

        //same parameters as add but name is sub
        line = {"num", "procedure", "sub", "(", "num", "a", ",", "num", "b", "num", "c", ")", "{"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);
        //2 procedure declared
        ASSERT_EQ(table.procedures.size(), 3);

        //same as sub
        line = {"num", "procedure", "sub", "(", "num", "a", ",", "num", "b", "num", "c", ")", "{"} ;
        expr = TranslateWordsToTokens(line, table.dataTypes);
        //try to declare a procedure we already have
        try {
            expr.EvaluateExpression(table);
            FAIL() << "Expected logic error when evaluating";
        }
        catch(std::logic_error const & err) {
            ASSERT_EQ(table.procedures.size(), 3);
        }
        catch(...) {
            FAIL() << "Expected logic error but got a different kind of error";
        }

    }

    TEST(ExpressionTests, EvaluateExpressionErrorTest){
        Table table = Table();

        std::vector<std::string> line = {"var1", "=", "2"};
        Expression expr = TranslateWordsToTokens(line, table.dataTypes);
        //try assigning an unassigned variable
        try {
            expr.EvaluateExpression(table);
            FAIL() << "Expected logic error when evaluating";
        }
        catch(std::logic_error const & err) {
            ASSERT_EQ(table.variableScopes.back().size(), 0);
        }
        catch(...) {
            FAIL() << "Expected logic error but got a different kind of error";
        }

        //create a good variable
        line = {"num", "test"};
        expr = TranslateWordsToTokens(line, table.dataTypes);
        expr.EvaluateExpression(table);
        ASSERT_EQ(table.variableScopes.back().size(), 1);

        //try to reference a variable that does not exist
        line = {"test", "=", "doesNotExist"};
        expr = TranslateWordsToTokens(line, table.dataTypes);
        try {
            expr.EvaluateExpression(table);
            FAIL() << "Expected logic error when evaluating";
        }
        catch(std::logic_error const & err) {
            //ensure we have not set the variable to anything
            ASSERT_EQ(table.variableScopes.back().back()->valueOfVariable, nullptr);
        }
        catch(...) {
            FAIL() << "Expected logic error but got a different kind of error";
        }

        //try to redeclare test
        line = {"num", "test"};
        expr = TranslateWordsToTokens(line, table.dataTypes);
        try {
            expr.EvaluateExpression(table);
            FAIL() << "Expected logic error when evaluating";
        }
        catch(std::logic_error const & err) {
            //ensure we did not declare it again
            ASSERT_EQ(table.variableScopes.back().size(), 1);
        }
        catch(...) {
            FAIL() << "Expected logic error but got a different kind of error";
        }

    }
}