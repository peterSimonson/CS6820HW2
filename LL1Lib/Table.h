//
// Created by Peter Simonson on 10/18/21.
//

#ifndef CS6820HW2_TABLE_H
#define CS6820HW2_TABLE_H


#include <vector>
#include <string>
#include <map>
#include "Nodes.h"
//Define the rows of the table
#define START_TOKEN 0
#define LINE_FULL_TOKEN 1
#define LINE_VAR_NAME 2
#define LINE_VAR_NAME_REMAINING 3
#define LINE_NUM_REMAINING 4
#define EXPR_TOKEN 5
#define L_TERM_TOKEN 6
#define R_TERM_TOKEN 7
#define EXPR_PRIME_TOKEN 8
#define TERM_PRIME_TOKEN 9
#define L_FACTOR_TOKEN 10
#define R_FACTOR_TOKEN 11
#define G_FACTOR_TOKEN 12
#define PARENS_EXPR_TOKEN 13
#define POSVAL_TOKEN 14
#define SPACE_NEG_VAL_TOKEN 15
#define VAR_TYPE 16
//Define Columns of our table
#define NUM_OF_NON_TERMINALS 17
#define END_TOKEN 17
#define EQUALS_TOKEN 18
#define PLUS_TOKEN 19
#define MINUS_TOKEN 20
#define MULTIPLY_TOKEN 21
#define DIVIDE_TOKEN 22
#define EXPONENT_TOKEN 23
#define OPEN_PARAN_TOKEN 24
#define CLOSE_PARAN_TOKEN 25
#define NAME_TOKEN 26
#define NUM_TOKEN 27
#define SPACE_NEG_NAME_TOKEN 28
#define SPACE_NEG_NUM_TOKEN 29
#define NEG_NAME_TOKEN 30
#define NEG_NUM_TOKEN 31
#define DATA_TYPE_TOKEN 32
#define EPSILON_TOKEN 33
//TODO: Change where this is used so it is the number of tokens not number of tokens - 1
#define NUM_OF_TOKENS 33

//other tokens
#define ERROR_TOKEN -1

//structure for a production rule
class rule{
public:
    int leftHandSide;
    std::vector<int> rightHandSide;
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
    //holds the data types
    std::vector<std::string> dataTypes;
    //holds the variables
    std::vector<VariableNode> variables;
    //holds the table
    int RuleTable [NUM_OF_TOKENS - NUM_OF_NON_TERMINALS][NUM_OF_NON_TERMINALS]{};

    int LookUpTable(int row, int column);
    void GenerateRules();
    void GenerateFirstSet();
    void GenerateFollowSet();
    void BuildTable();
    void addRule(int lhs, std::vector<int>&& rhs);
    std::vector<int> findFirstPlusSet(rule production);
    bool is_already_a_var(const std::string& nameOfVariable);
    VariableNode * GetVariable(const std::string& nameOfVariableToReturn);
    bool AddVariable(const VariableNode& varToAdd);
};

std::vector<int> removeEpsilonFromSet(std::vector<int> set);
std::vector<int> unionize_sets(const std::vector<int>& firstSet, const std::vector<int>& secondSet);
bool is_number(const std::string& s);
bool is_decimal_number(const std::string& number);
bool is_Neg_Num(const std::string& s);
bool is_name(const std::string& s);
bool is_Neg_Name(const std::string& s);
bool is_terminal(const int& token);
bool is_Value_Token(int token);
bool set_contains_epsilon(std::vector<int> set);
bool is_data_type(const std::string& word, const std::vector<std::string>& dataTypes);

#endif //CS6820HW2_TABLE_H
