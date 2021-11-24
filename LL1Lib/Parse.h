//
// Created by Peter Simonson on 10/17/21.
//

#ifndef CS6820HW2_PARSE_H
#define CS6820HW2_PARSE_H

#include <vector>
#include <string>
#include "Table.h"
#include "Expression.h"

class Parser{
public:
    explicit Parser(const std::string& line, Table& table);
    bool successfulParse;
    //contains the expression
    Expression expr;
    void EvaluateLine(Table& table);
    void SwapStack(int ruleIndex, std::vector<int> & stack, Table table);
};

std::vector<std::string> parseWords(std::string const& line);

#endif //CS6820HW2_PARSE_H
