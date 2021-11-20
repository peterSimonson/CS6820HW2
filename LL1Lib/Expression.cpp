//
// Created by Peter Simonson on 11/11/21.
//

#include <stack>
#include <algorithm>
#include "Expression.h"
#include "Nodes.h"
#include <stdexcept>

/// function to find the precedence level of an operator. Taken from: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
/// \param operation check the precedence of the operator
/// \return
int precedenceOfOperator(std::string operation)
{
    switch (operation.at(0))
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

/// Converts the infix vector of strings in text into a post-fix vector of string
/// Function was taken and modified from: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
/// \return post-fix vector of strings created from strings in text
std::vector<std::string> convertTextToPostFix(const std::vector<std::string>& infixExpression) {
    std::vector<std::string> postFixExpression;
    std::vector<std::string> stack;

    //loop through all words in the expression
    for(auto & word : infixExpression){

        //if it is a variable, put it on the expression
        if(is_name(word) || is_number(word)){
            postFixExpression.push_back(word);
        }
            //add the open paran to the stack. We will look for it once we encounter the close paran
        else if(word == "("){
            stack.push_back(word);
        }
            //if we have a closing paran look for all teh operators before the open paran
        else if(word == ")"){
            while(!stack.empty() && stack.back() != "("){
                //add the operator to the postfix expression
                postFixExpression.push_back(stack.back());
                stack.pop_back();
            }
            //remove the open paran
            stack.pop_back();
        }
            //else we have an operator
        else{
            int precedenceOfWord = precedenceOfOperator(word);
            //take all operators off the stack that have a precedence equal to or greater than word
            while(!stack.empty() && precedenceOfWord <= precedenceOfOperator(stack.back())){
                postFixExpression.push_back(stack.back());
                stack.pop_back();
            }
            //put word onto the stack
            stack.push_back(word);
        }
    }

    //take all remaining operators off the stack
    while(!stack.empty()){
        postFixExpression.push_back(stack.back());
        stack.pop_back();
    }

    return postFixExpression;
}

/// Evaluates a postfix expression
/// \param postFixExpression the post-fix expression you wish to evaluate
/// \return the value of the post-fix expression
TreeNode *evaluatePostFix(const std::vector<std::string> &postFixExpression, Table table) {

    //holds the stack needed to evaluate
    std::stack<TreeNode*> stack;
    //loop through each term in the post-fix expression
    for(auto & word : postFixExpression){
        //if word is a number, create an int node and push it to the stack
        if(is_number(word)){
            if(is_decimal_number(word)){
                auto * decimalNode = new DecimalNode(std::stod(word));
                stack.push(decimalNode);
            }
            //if it isn't a decimal it is an integer
            else{
                auto * intNode = new IntegerNode(std::stoi(word));
                stack.push(intNode);
            }

        }
        //if it is a variable
        else if(is_name(word)){
            auto * variableNode = table.GetVariable(word);
            //if the variable is not declared throw an error
            if(variableNode == nullptr){
                throw std::logic_error(word + " is an undeclared or out of scope variable being referenced\n");
            }
            stack.push(variableNode);
        }
        //otherwise, we have an operator
        else{
            auto * value1 = stack.top();
            stack.pop();
            auto * value2 = stack.top();
            stack.pop();

            if(word == "+"){
                auto * addNode = new AddNode(value2, value1);
                stack.push(addNode);
            }
            else if(word == "-"){
                auto * subNode = new SubtractNode(value2, value1);
                stack.push(subNode);
            }
            else if(word == "*"){
                auto * multiplyNode = new MultiplyNode(value2, value1);
                stack.push(multiplyNode);
            }
            else if(word == "/"){
                auto * divideNode = new DivideNode(value2, value1);
                stack.push(divideNode);
            }
            else if(word == "^"){
                auto * exponentNode = new ExponentNode(value2, value1);
                stack.push(exponentNode);
            }
            //else if it is a function call
        }
    }
    //return the result of the evaluation
    return stack.top();
}

/// Takes the parsed words and translates them into a collection of tokens that the LL1 parser understands
/// \param words the words you wish to translate to an understandable format
/// \param dataTypes the data types that could occur in words
/// \return An expression object with all the tokens and all the words for the expression
Expression TranslateWordsToTokens(std::vector<std::string> words, const std::vector<std::string>& dataTypes) {
    //used to loop through the vector of strings
    std::vector<std::string>::iterator str;
    //will hold all the strings we translated to int tokens
    std::vector<int> tokens;
    //hold all the text of the expression
    std::vector<std::string> text;

    for(str = words.begin(); str != words.end(); str++){
        std::string word = *str;
        //check what type of token this is

        if(is_number(word)){
            tokens.push_back(NUM_TOKEN);
            text.push_back(word);
        }
        else if(is_data_type(word, dataTypes)){
            tokens.push_back(DATA_TYPE_TOKEN);
            text.push_back(word);
        } else if(word == "procedure") {
            tokens.push_back(PROCEDURE_TOKEN);
            text.push_back(word);
        }
        else if(is_name(word)){
            tokens.push_back(NAME_TOKEN);
            text.push_back(word);
        }
            //if the first char is a space check if everything else is a num
        else if(word.at(0) == ' ' && is_Neg_Num(word.substr(1, word.size()))){
            //if the last token is a value token we have a subtraction operation
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NUM_TOKEN);
            }
                //otherwise, we have a negative num
            else{
                tokens.push_back(SPACE_NEG_NUM_TOKEN);
            }
            text.emplace_back("-");
            text.push_back(word.substr(2, word.size()));
        }
        //if the first char is a space check if everything else is a name
        else if(word.at(0) == ' ' && is_Neg_Name(word.substr(1, word.size()))){
            //if the last token is a value token we have a subtraction operation
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NAME_TOKEN);
            }
                //otherwise, we have a negative num
            else{
                tokens.push_back(SPACE_NEG_NAME_TOKEN);
            }
            text.emplace_back("-");
            text.push_back(word.substr(2, word.size()));
        }
            //if the first char is a negative check if everything else is a num
        else if(word.at(0) == '-' && is_number(word.substr(1, word.size()))){
            //if the last token is a value token we have a subtraction operation
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NUM_TOKEN);
            }
                //otherwise, we have a negative num
            else{
                tokens.push_back(NEG_NUM_TOKEN);
            }
            text.emplace_back("-");
            text.push_back(word.substr(1, word.size()));
        }
            //if the first char is a negative check if everything else is a name
        else if(word.at(0) == '-' && is_name(word.substr(1, word.size()))){
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NAME_TOKEN);
            }
            else{
                tokens.push_back(NEG_NAME_TOKEN);
            }
            text.emplace_back("-");
            text.push_back(word.substr(1, word.size()));
        }
        else if(word == "+"){
            tokens.push_back(PLUS_TOKEN);
            text.push_back(word);
        }
        else if(word == "-" || word == " -"){
            tokens.push_back(MINUS_TOKEN);
            text.emplace_back("-");
        }
        else if(word == "*"){
            tokens.push_back(MULTIPLY_TOKEN);
            text.push_back(word);
        }
        else if(word == "/"){
            tokens.push_back(DIVIDE_TOKEN);
            text.push_back(word);
        }
        else if(word == "^"){
            tokens.push_back(POWER_TOKEN);
            text.push_back(word);
        }
        else if(word == "="){
            tokens.push_back(EQUALS_TOKEN);
            text.push_back(word);
        } 
        else if(word == "("){
            tokens.push_back(OPEN_PAREN_TOKEN);
            text.push_back(word);
        }
        else if(word == ")"){
            tokens.push_back(CLOSE_PAREN_TOKEN);
            text.push_back(word);
        }
        else if(word == "{"){
            tokens.push_back(OPEN_CURLY_TOKEN);
            text.push_back(word);
        }
        else if(word == "}"){
            tokens.push_back(CLOSE_CURLY_TOKEN);
            text.push_back(word);
        }
        else if(word == ","){
            tokens.push_back(COMMA_TOKEN);
            text.push_back(word);
        }
            //if we could not find a match than push an error token
        else{
            tokens.push_back(ERROR_TOKEN);
            break;
        }
    }

    //push the end of file to the end of the vector
    tokens.push_back(END_TOKEN);

    return {tokens, text};
}

void Expression::EvaluateExpression(Table& table) {

    //are we declaring a new variable
    if(tokens.front() == DATA_TYPE_TOKEN){
        DeclareNewVariable(table);
    }
    //look for a equals sign
    auto it = std::find(tokens.begin(), tokens.end(), EQUALS_TOKEN);
    //if we have an equals sign we are performing an assignment operation
    if( it != tokens.end()){
        int indexOfEqualsSign = (int)(it - tokens.begin());
        PerformAssignmentOperation(table, indexOfEqualsSign);
    }
}

void Expression::PerformAssignmentOperation(Table& table, int indexOfEquals) {
    std::string variableName;
    VariableNode * variable;

    //the variable name is one before the equals
    variableName = words[indexOfEquals - 1];
    //look up the variable name
    variable = table.GetVariable(variableName);
    //check if we were able to look up the variable
    if(variable == nullptr){
        //if it is not previously declared throw an error
        throw std::logic_error(variableName + " is an undeclared or out of scope variable being assigned to\n");
    }
    //get words after the equals sign. This is our infix expression
    std::vector<std::string> infix(words.begin() + (indexOfEquals + 1), words.end());
    //convert infix to postfix
    std::vector<std::string> postfix  = convertTextToPostFix(infix);
    //evaluate the expression in postfix form
    TreeNode * valueOfVariable = evaluatePostFix(postfix, table);
    //assign the evaluated value to the variable
    variable->AssignValue(valueOfVariable);
}

void Expression::DeclareNewVariable(Table& table) {
    std::string variableName;
    //variable type is the first word
    std::string variableType = words[0];
    //the variable name is the second word
    variableName = words[1];
    //create the unassigned variable
    VariableNode variable = VariableNode(nullptr, variableName, variableType);

    if(!table.AddVariable(variable)){
        throw std::logic_error(variableName + " is being declared multiple times\n");
    }
}
