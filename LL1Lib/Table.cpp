//
// Created by Peter Simonson on 10/18/21.
//

#include "Table.h"

bool is_number(const std::string& s);
bool is_name(const std::string& s);

std::vector<int> TranslateWordsToTokens(std::vector<std::string> words) {
    //used to loop through the vector of strings
    std::vector<std::string>::iterator str;
    //will hold all the strings we translated to int tokens
    std::vector<int> tokens;

    //push the end of file to the base of the stack
    tokens.push_back(END_TERM);

    for(str = words.begin(); str != words.end(); str++){
        //check what type of token this is
        if(is_number(*str)){
            tokens.push_back(NUM_TERM);
        }
        else if(is_name(*str)){
            tokens.push_back(NAME_TERM);
        }
        else if(*str == "+"){
            tokens.push_back(PLUS);
        }
        else if(*str == "-"){
            tokens.push_back(MINUS);
        }
        else if(*str == "*"){
            tokens.push_back(MULTIPLY);
        }
        else if(*str == "/"){
            tokens.push_back(DIVIDE);
        }
        else if(*str == "("){
            tokens.push_back(OPEN_PARAN);
        }
        else if(*str == ")"){
            tokens.push_back(CLOSE_PARAN);
        }
        //if we could not find a match than push an error token
        else{
            tokens.push_back(ERROR_TOKEN);
        }
    }

    return tokens;
}


//the functions is_number and is_name were taken from:
//https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_name(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isalnum(*it)) ++it;
    return !s.empty() && it == s.end();
}