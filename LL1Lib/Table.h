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
#define EXPR_PRIME_TOKEN 2
#define TERM_TOKEN 3
#define TERM_PRIME_TOKEN 4
#define FACTOR_TOKEN 5
//Define Columns of our table
#define NUM_OF_NON_TERMINALS 6
#define END_TOKEN 6
#define PLUS_TOKEN 7
#define MINUS_TOKEN 8
#define MULTIPLY_TOKEN 9
#define DIVIDE_TOKEN 10
#define OPEN_PARAN_TOKEN 11
#define CLOSE_PARAN_TOKEN 12
#define NAME_TOKEN 13
#define NUM_TOKEN 14
#define EPSILON_TOKEN 15
#define NUM_OF_TOKENS 15

//other tokens
#define ERROR_TOKEN -1

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
std::vector<int> TranslateWordsToTokens(std::vector<std::string> words);
std::vector<int> unionize_sets(const std::vector<int>& firstSet, const std::vector<int>& secondSet);
bool is_number(const std::string& s);
bool is_name(const std::string& s);
bool is_terminal(const int& token);
bool set_contains_epsilon(std::vector<int> set);

#endif //CS6820HW2_TABLE_H
