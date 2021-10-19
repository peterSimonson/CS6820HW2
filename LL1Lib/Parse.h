//
// Created by Peter Simonson on 10/17/21.
//

#ifndef CS6820HW2_PARSE_H
#define CS6820HW2_PARSE_H

#include <vector>
#include <string>
#include "Table.h"

class Parser{
    explicit Parser(const std::string& line);
    //contains the input words as tokens
    std::vector<int> inputTokens;
    //contains the tokens on the stack
    std::vector<int> stack;
};

std::vector<std::string> parseWords(std::string const& line);

#endif //CS6820HW2_PARSE_H
