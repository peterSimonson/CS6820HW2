//
// Created by Peter Simonson on 10/18/21.
//

#include "Table.h"

/// Translates an array of strings into an arroy of tokens that correspond to each string
/// If the string does not have a matching token it will be represented with an error token
/// \param words The strings you wish to translate to tokens
/// \return a list of token corresponding to the strings that were entered
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

/// Checks if a token is a terminal token
/// \param token integer token you wish to check if it is a terminal
/// \return Returns true if the token is a terminal. False if it is not a terminal
bool is_terminal(const int &token) {
    if(token >= 6 && token <= 14){
        return true;
    }
    else{
        return false;
    }
}

/// Looks up the rule in figure 3.11 b
/// \param column the token corresponding to the table column you wish to look up
/// \param row the token corresponding to the table row you wish to look up
/// \return the entry at the row and column you specify
int Table::LookUpTable(int column, int row) {
    return RuleTable[column - COLUMN_OFFSET][row];
}
