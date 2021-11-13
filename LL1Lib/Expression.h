//
// Created by Peter Simonson on 11/11/21.
//

#ifndef CS6820HW2_EXPRESSION_H
#define CS6820HW2_EXPRESSION_H

#include "string"
#include "vector"
#include "Table.h"


class Expression {
public:
    //the tokenized words of the expression
    std::vector<int> tokens;
    //the text of the expression used to find postfix format
    std::vector<std::string> infix;
};
std::vector<std::string> convertTextToPostFix(const std::vector<std::string>& infixExpression);
Expression TranslateWordsToTokens(std::vector<std::string> words);
double evaluatePostFixExpression(const std::vector<std::string>& postFixExpression);

#endif //CS6820HW2_EXPRESSION_H
