//
// Created by Peter Simonson on 11/11/21.
//

#include "Expression.h"

/// function to find the precedence level of an operator. Taken from: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
/// \param opeartor
/// \return
int precedenceOfOperator(std::string opeartor)
{
    switch (opeartor.at(0))
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

/// Converts the strings in text to a post-fix string
/// Function was taken and modified from: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
/// \return post-fix string created from strings in text
std::string Expression::convertToPostFix(){
    std::string postFixExpression;
    std::vector<std::string> stack;

    //loop through all words in the expression
    for(auto & word : text){

        //if it is a variable, put it on the expression
        if(is_name(word) || is_number(word)){
            postFixExpression += word;
        }
            //add the open paran to the stack. We will look for it once we encounter the close paran
        else if(word == "("){
            stack.push_back(word);
        }
            //if we have a closing paran look for all teh operators before the open paran
        else if(word == ")"){
            while(!stack.empty() && stack.back() != "("){
                //add the operator to the postfix expression
                postFixExpression += stack.back();
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
                postFixExpression += stack.back();
                stack.pop_back();
            }
            //put word onto the stack
            stack.push_back(word);
        }
    }

    //take all remaining operators off the stack
    while(!stack.empty()){
        postFixExpression += stack.back();
        stack.pop_back();
    }

    return postFixExpression;
}

Expression TranslateWordsToTokens(std::vector<std::string> words) {
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
            tokens.push_back(EXPONENT_TOKEN);
            text.push_back(word);
        }
        else if(word == "("){
            tokens.push_back(OPEN_PARAN_TOKEN);
            text.push_back(word);
        }
        else if(word == ")"){
            tokens.push_back(CLOSE_PARAN_TOKEN);
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
