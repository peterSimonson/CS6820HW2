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

        expr = "42 42";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "42");
        ASSERT_EQ(words[1], "42");
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

    TEST(ParseTests, ParseNegNameTest){
        std::string expr = "-testVar";
        std::vector<std::string> words = parseWords(expr);
        ASSERT_EQ(words[0], "-testVar");

        expr = "2 + -testVar";
        words = parseWords(expr);

        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], " -testVar");

        expr = "2 - testVar";
        words = parseWords(expr);

        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -testVar");

        expr = "2 - -testVar";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -");
        ASSERT_EQ(words[2], " -testVar");

        expr = "2 --testVar";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -");
        ASSERT_EQ(words[2], "-testVar");

        expr = "2 ++testVar";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "+");
        ASSERT_EQ(words[3], "testVar");

        expr = "2 +-testVar";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], "+");
        ASSERT_EQ(words[2], "-testVar");

        expr = "2 -+testVar";
        words = parseWords(expr);
        ASSERT_EQ(words[0], "2");
        ASSERT_EQ(words[1], " -");
        ASSERT_EQ(words[2], "+");
        ASSERT_EQ(words[3], "testVar");
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

        expr = "ish peter = 2 + chai";

        words = parseWords(expr);
        std::vector<std::string> result = {"ish", "peter", "=", "2", "+", "chai"};
        ASSERT_EQ(words, result);
    }

    TEST(ParseTests, ParseStringTest){
        std::string expr = "printString \"hello, world\"";
        std::vector<std::string> words = parseWords(expr);
        std::vector<std::string> result = {"printString", "\"hello, world\""};
        ASSERT_EQ(words, result);

        expr = "printString \"2+2 * 3 =peter\"";
        words = parseWords(expr);
        result = {"printString", "\"2+2 * 3 =peter\""};
        ASSERT_EQ(words, result);

        expr = "printString \"2+2 * 3 =peter";

        try{
            //We needed an end quote
            parseWords(expr);
            FAIL() << "Expected range error";
        }
        catch(std::range_error const & err) {

        }
        catch(...) {
            FAIL() << "Expected runtime error";
        }
    }

    TEST(ParseTests, ParseProcedureTest){
        std::string expr = "num procedure add(num a, num b) {";

        std::vector<std::string> words = parseWords(expr);
        std::vector<std::string> result = {"num", "procedure", "add", "(", "num", "a", ",", "num", "b", ")","{"};
        ASSERT_EQ(words, result);

        expr = "}";
        words = parseWords(expr);
        result = {"}"};
        ASSERT_EQ(words, result);

        expr = "}";
        words = parseWords(expr);
        result = {"}"};
        ASSERT_EQ(words, result);

        expr = "num result6 = add(a, b) - mult(a, b)";
        words = parseWords(expr);
        result = {"num", "result6", "=", "add", "(", "a", ",", "b", ")", " -mult", "(", "a", ",", "b", ")"};
        ASSERT_EQ(words, result);
    }


    TEST(ParseTests, InvalidParseTest){
        std::ifstream file("../TestResources/BadExpressions.txt");//holds file we are opening
        std::string line; //holds a single expression we wish to parse

        ASSERT_TRUE(file.is_open());

        //generate our table
        Table table = Table();

        //read each line from the file
        while (std::getline(file, line)){
            Parser parse = Parser(line, table);
            //each one of these parses should fail
            EXPECT_FALSE(parse.successfulParse);
        }

        //close input file
        file.close();
    }

    TEST(ParseTests, ValidParseTest){
        std::ifstream file("../TestResources/GoodExpressions.txt");//holds file we are opening
        std::string line; //holds a single expression we wish to parse

        ASSERT_TRUE(file.is_open());

        //generate our table
        Table table = Table();

        //read each line from the file
        while (std::getline(file, line)){
            Parser parse = Parser(line, table);
            //each one of these parses should fail
            EXPECT_TRUE(parse.successfulParse);
        }

        //close input file
        file.close();
    }

    TEST(ParseTests, ProcedureParseTest){
        std::ifstream file("../TestResources/Procedures.txt");//holds file we are opening
        std::string line; //holds a single expression we wish to parse

        ASSERT_TRUE(file.is_open());

        //generate our table
        Table table = Table();

        //read each line from the file
        while (std::getline(file, line)){
            Parser parse = Parser(line, table);
            //each one of these parses should fail
            EXPECT_TRUE(parse.successfulParse);
        }

        //close input file
        file.close();
    }

    TEST(ParseTests, LeftMidAndRightTest){
        Table table = Table();

        Parser parser = Parser("4 * 5", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("num var = 4 * 5", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("var = 4 * 5", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("var", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("num var", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("num", table);
        EXPECT_FALSE(parser.successfulParse);

        parser = Parser("num var 4 * 5", table);
        EXPECT_FALSE(parser.successfulParse);

        parser = Parser("var 4 * 5", table);
        EXPECT_FALSE(parser.successfulParse);

        parser = Parser("num = 4 * 5", table);
        EXPECT_FALSE(parser.successfulParse);

        parser = Parser("num var = num var + 4 * 5", table);
        EXPECT_FALSE(parser.successfulParse);

        parser = Parser("num var1 =  4 * (num var2) + 5", table);
        EXPECT_FALSE(parser.successfulParse);
    }

    TEST(ParserTest, UpdatedEdgeParseCases){
        Table table = Table();

        Parser parser = Parser("-var1", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("(var + 3) * 2", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("-(var + 3)", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("var1 = -(var + 3)", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("-(var + 3) + 2", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("var1 = -(var + 3) + 2", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("var1 = 2 -(var + 3) + 2", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("var1 = -var1 -(var + 3) + 2", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("var1 = -(var + 3) - (var + 3) + 2", table);
        EXPECT_TRUE(parser.successfulParse);

        parser = Parser("(1 + 2)", table);
        EXPECT_TRUE(parser.successfulParse);
    }

    TEST(ParserTests, SimpleNegativeEvalTest){
        std::string line = "num var1 = 1-2";

        Table table = Table();
        AssemblyFile file = AssemblyFile();
        Parser parse = Parser(line, table);

        ASSERT_TRUE(parse.successfulParse);
        parse.EvaluateLine(table, file);

        ASSERT_EQ(table.variableScopes.back().back()->EvaluateNode(), -1);

        line = "num var2 = -3";
        parse = Parser(line, table);

        ASSERT_TRUE(parse.successfulParse);
        parse.EvaluateLine(table, file);

        ASSERT_EQ(table.variableScopes.back().back()->EvaluateNode(), -3);

        line = "num var22 = -1 * 8 / -1";
        parse = Parser(line, table);

        ASSERT_TRUE(parse.successfulParse);
        parse.EvaluateLine(table, file);

        ASSERT_EQ(table.variableScopes.back().back()->EvaluateNode(), 8);
    }

    TEST(ParserTests, SimpleDivideByZeroEvalTest){

        std::string line = "num var1 = 5 / 0";

        Table table = Table();
        AssemblyFile file = AssemblyFile();
        Parser parse = Parser(line, table);

        //try to divide by zero
        try {
            parse.EvaluateLine(table, file);
            table.variableScopes.back().back()->EvaluateNode();
            FAIL() << "Expected runtime error";
        }
        catch(std::logic_error const & err) {
            EXPECT_EQ(err.what(),std::string("Error: Attempted to divide by zero\n"));
        }
        catch(...) {
            FAIL() << "Expected runtime error";
        }
    }
}