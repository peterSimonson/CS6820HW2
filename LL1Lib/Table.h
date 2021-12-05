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
#define PROCEDURE_PARAMS_TOKEN 4
#define PROCEDURE_ARGS_TOKEN 5
#define PARAMS_TOKEN 6
#define ARGS_TOKEN 7
#define MORE_PARAMS_TOKEN 8
#define MORE_ARGS_TOKEN 9
#define EXPR_TOKEN 10
#define L_TERM_ADD_SUB_TOKEN 11
#define R_TERM_ADD_SUB_TOKEN 12
#define ADD_SUB_PRIME_TOKEN 13
#define L_TERM_MULT_DIV_TOKEN 14
#define R_TERM_MULT_DIV_TOKEN 15
#define MULT_DIV_PRIME_TOKEN 16
#define MULT_AND_RIGHT_OP_TOKEN 17
#define DIV_AND_RIGHT_OP_TOKEN 18
#define L_TERM_POWER_TOKEN 19
#define R_TERM_POWER_TOKEN 20
#define POWER_PRIME_TOKEN 21
#define POWER_AND_RIGHT_OP_TOKEN 22
#define G_FACTOR_TOKEN 23
#define PARENS_EXPR_TOKEN 24
#define POSVAL_TOKEN 25
#define SPACE_NEG_VAL_TOKEN 26
#define VAR_TYPE_TOKEN 27
//Define Columns of our table
#define NUM_OF_NON_TERMINALS 28
#define END_TOKEN 28
#define PROCEDURE_TOKEN 29
#define COMMA_TOKEN 30
#define EQUALS_TOKEN 31
#define PLUS_TOKEN 32
#define MINUS_TOKEN 33
#define MULTIPLY_TOKEN 34
#define DIVIDE_TOKEN 35
#define POWER_TOKEN 36
#define OPEN_PAREN_TOKEN 37
#define CLOSE_PAREN_TOKEN 38
#define OPEN_CURLY_TOKEN 39
#define CLOSE_CURLY_TOKEN 40
#define NAME_TOKEN 41
#define NUM_TOKEN 42
#define SPACE_NEG_NAME_TOKEN 43
#define SPACE_NEG_NUM_TOKEN 44
#define NEG_NAME_TOKEN 45
#define NEG_NUM_TOKEN 46
#define DATA_TYPE_TOKEN 47
#define RETURN_TOKEN 48
#define EPSILON_TOKEN 49
//TODO: Change where this is used so it is the number of tokens not number of tokens - 1
#define NUM_OF_TOKENS 49

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
    void CleanUpTable();
    //holds the first set
    std::map<int, std::vector<int>> firstSet;
    //holds the follow set
    std::map<int, std::vector<int>> followSet;
    //holds the productions
    std::map<int, rule> rules;
    //holds the data types
    std::vector<std::string> dataTypes;
    //Vector of vectors that holds the variable scopes
    std::vector<std::vector<std::shared_ptr<VariableNode>>> variableScopes;
    //holds the procedures
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
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
    std::shared_ptr<VariableNode> GetVariable(const std::string& nameOfVariableToReturn);
    std::shared_ptr<ProcedureNode> GetProcedure(const std::string& nameOfProcedureToReturn, std::vector<std::shared_ptr<TreeNode>> functionArguments);
    bool AddVariable(const std::shared_ptr<VariableNode>& varToAdd);
    bool AddProcedure(const ProcedureNode& procedureToAdd);
    void AddVariableScope();
    void RemoveVariableScope();
};

std::vector<int> removeEpsilonFromSet(std::vector<int> set);
std::vector<int> unionize_sets(const std::vector<int>& firstSet, const std::vector<int>& secondSet);
bool is_number(const std::string& s);
bool is_positive_number(const std::string& s);
bool is_decimal_number(const std::string& number);
bool is_Neg_Num(const std::string& s);
bool is_name(const std::string& s);
bool is_positive_name(const std::string& s);
bool is_Neg_Name(const std::string& s);
bool is_terminal(const int& token);
bool is_Value_Token(int token);
bool set_contains_epsilon(std::vector<int> set);
bool is_data_type(const std::string& word, const std::vector<std::string>& dataTypes);
bool is_procedure_call(const std::string& word);

#endif //CS6820HW2_TABLE_H
