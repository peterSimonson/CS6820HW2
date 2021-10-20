//
// Created by Peter Simonson on 10/18/21.
//

#ifndef CS6820HW2_TABLE_H
#define CS6820HW2_TABLE_H


#include <vector>
#include <string>
//Define the rows of the table
#define GOAL_TOKEN 0
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

//other tokens
#define ERROR_TOKEN -1


class Table {

};

std::vector<int> TranslateWordsToTokens(std::vector<std::string> words);
bool is_number(const std::string& s);
bool is_name(const std::string& s);

#endif //CS6820HW2_TABLE_H
