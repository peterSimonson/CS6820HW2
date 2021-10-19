//
// Created by Peter Simonson on 10/18/21.
//

#ifndef CS6820HW2_TABLE_H
#define CS6820HW2_TABLE_H


#include <vector>
#include <string>
//Define the rows of the table
#define GOAL 0
#define EXPR 1
#define EXPR_PRIME 2
#define TERM 3
#define TERM_PRIME 4
#define FACTOR 5
//Define Columns of our table
#define COLUMN_OFFSET 6
#define END_TERM 6
#define PLUS 7
#define MINUS 8
#define MULTIPLY 9
#define DIVIDE 10
#define OPEN_PARAN 11
#define CLOSE_PARAN 12
#define NAME_TERM 13
#define NUM_TERM 14

//other tokens
#define ERROR_TOKEN -1


class Table {

};

std::vector<int> TranslateWordsToTokens(std::vector<std::string> words);

#endif //CS6820HW2_TABLE_H
