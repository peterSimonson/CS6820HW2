//
// Created by Peter Simonson on 10/18/21.
//

#include "Table.h"

std::vector<int> TranslateWordsToTokens(std::vector<std::string> words) {
    //used to loop through the vector of strings
    std::vector<std::string>::iterator str;
    //will hold all the strings we translated to int tokens
    std::vector<int> tokens;

    //push the end of file to the base of the stack
    tokens.push_back(END_TOKEN);

    for(str = words.begin(); str != words.end(); str++){
        //check what type of token this is
        if(is_number(*str)){
            tokens.push_back(NUM_TOKEN);
        }
        else if(is_name(*str)){
            tokens.push_back(NAME_TOKEN);
        }
        else if(*str == "+"){
            tokens.push_back(PLUS_TOKEN);
        }
        else if(*str == "-"){
            tokens.push_back(MINUS_TOKEN);
        }
        else if(*str == "*"){
            tokens.push_back(MULTIPLY_TOKEN);
        }
        else if(*str == "/"){
            tokens.push_back(DIVIDE_TOKEN);
        }
        else if(*str == "("){
            tokens.push_back(OPEN_PARAN_TOKEN);
        }
        else if(*str == ")"){
            tokens.push_back(CLOSE_PARAN_TOKEN);
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

/// Checks if a string is a number
/// note: does not accept '-' or '.' as part of a number
/// \param s string we want to check if it is a number
/// \return true if it is a number, false if it is not
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/// Check if a string is a name or not
/// We check that the first char is a letter and the rest are alphanumeric
/// \param s string we want to check if it is a name
/// \return True if a name, false if it is not
bool is_name(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    //first char must be a letter
    if(std::isalpha(*it)){
        it++;
        //check the remaining numbers are alphanumeric
        while (it != s.end() && std::isalnum(*it)) ++it;
        return !s.empty() && it == s.end();
    }
    else{
        return false;
    }

}
