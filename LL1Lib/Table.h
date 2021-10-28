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
#define COLUMN_OFFSET 6
#define END_TOKEN 6
#define PLUS_TOKEN 7
#define MINUS_TOKEN 8
#define MULTIPLY_TOKEN 9
#define DIVIDE_TOKEN 10
#define OPEN_PARAN_TOKEN 11
#define CLOSE_PARAN_TOKEN 12
#define NAME_TOKEN 13
#define NUM_TOKEN 14
#define NUMBER_OF_TOKENS 14

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
    std::map<int, rule> rules;

    //the token table is a 6x9 table that holds the values for the token swap function
    int RuleTable [9][6] = {
            {ERROR_TOKEN, ERROR_TOKEN, 4, ERROR_TOKEN, 8, ERROR_TOKEN}, //Column 1
            {ERROR_TOKEN, ERROR_TOKEN, 2, ERROR_TOKEN, 8, ERROR_TOKEN}, //Column 2
            {ERROR_TOKEN, ERROR_TOKEN, 3, ERROR_TOKEN, 8, ERROR_TOKEN}, //Column 3
            {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 6, ERROR_TOKEN},
            {ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, ERROR_TOKEN, 7, ERROR_TOKEN},
            {0, 1, ERROR_TOKEN, 5, ERROR_TOKEN, 9},
            {ERROR_TOKEN, ERROR_TOKEN, 4, ERROR_TOKEN, 8, ERROR_TOKEN},
            {0, 1, ERROR_TOKEN, 5, ERROR_TOKEN, 11},
            {0, 1, ERROR_TOKEN, 5, ERROR_TOKEN, 10}
    };
    int LookUpTable(int row, int column);
    void GenerateRules();
    void GenerateFirstSet();
    void GenerateFollowSet();
};

std::vector<int> TranslateWordsToTokens(std::vector<std::string> words);
bool is_number(const std::string& s);
bool is_name(const std::string& s);
bool is_terminal(const int& token);

#endif //CS6820HW2_TABLE_H
