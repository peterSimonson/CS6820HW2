//
// Created by Peter Simonson on 10/17/21.
//

#ifndef CS6820HW2_PARSE_H
#define CS6820HW2_PARSE_H

#include <vector>
#include <string>
#include "Table.h"

class Parser{
public:
    explicit Parser(const std::string& line, Table table);
    bool successfulParse;
    //contains the expression
    Expression expr;
    Table table;
    //hold the postfix expression
    std::string postfix;

    void SwapStack(int ruleIndex, std::vector<int> & stack);
};

std::vector<std::string> parseWords(std::string const& line);

#endif //CS6820HW2_PARSE_H
