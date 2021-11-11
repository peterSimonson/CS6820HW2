//
// Created by Peter Simonson on 10/18/21.
//

#ifndef CS6820HW2_TABLE_H
#define CS6820HW2_TABLE_H


#include <vector>
#include <string>
#include <map>
//Define the rows of the table
#define START_TOKEN 0
#define EXPR_TOKEN 1
#define L_TERM_TOKEN 2
#define R_TERM_TOKEN 3
#define EXPR_PRIME_TOKEN 4
#define TERM_PRIME_TOKEN 5
#define L_FACTOR_TOKEN 6
#define R_FACTOR_TOKEN 7
#define G_FACTOR_TOKEN 8
#define POSVAL_TOKEN 9
#define SPACE_NEG_VAL_TOKEN 10
//Define Columns of our table
#define NUM_OF_NON_TERMINALS 11
#define END_TOKEN 11
#define PLUS_TOKEN 12
#define MINUS_TOKEN 13
#define MULTIPLY_TOKEN 14
#define DIVIDE_TOKEN 15
#define EXPONENT_TOKEN 16
#define OPEN_PARAN_TOKEN 17
#define CLOSE_PARAN_TOKEN 18
#define NAME_TOKEN 19
#define NUM_TOKEN 20
#define SPACE_NEG_NAME_TOKEN 21
#define SPACE_NEG_NUM_TOKEN 22
#define NEG_NAME_TOKEN 23
#define NEG_NUM_TOKEN 24
#define EPSILON_TOKEN 25
#define NUM_OF_TOKENS 25

//other tokens
#define ERROR_TOKEN -1

//structure for a production rule
class rule{
public:
    int leftHandSide;
    std::vector<int> rightHandSide;
};

//holds the data for an expression
class Expression{
public:
    //the tokenized words of the expression
    std::vector<int> tokens;
    //the text of the expression used to find postfix format
    std::vector<std::string> text;
};

class Table {
public:
    Table();
    //holds the first set
    std::map<int, std::vector<int>> firstSet;
    //holds the follow set
    std::map<int, std::vector<int>> followSet;
    //holds the productions
    std::map<int, rule> rules;
    //holds the table
    int RuleTable [NUM_OF_TOKENS - NUM_OF_NON_TERMINALS][NUM_OF_NON_TERMINALS]{};

    int LookUpTable(int row, int column);
    void GenerateRules();
    void GenerateFirstSet();
    void GenerateFollowSet();
    void BuildTable();
    std::vector<int> findFirstPlusSet(rule production);
};

std::vector<int> removeEpsilonFromSet(std::vector<int> set);
Expression TranslateWordsToTokens(std::vector<std::string> words);
std::vector<int> unionize_sets(const std::vector<int>& firstSet, const std::vector<int>& secondSet);
bool is_number(const std::string& s);
bool is_Neg_Num(const std::string& s);
bool is_name(const std::string& s);
bool is_Neg_Name(const std::string& s);
bool is_terminal(const int& token);
bool is_Value_Token(int token);
bool set_contains_epsilon(std::vector<int> set);

#endif //CS6820HW2_TABLE_H
