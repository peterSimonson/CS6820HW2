//
// Created by Peter Simonson on 10/18/21.
//

#include "Table.h"

/// Translates an array of strings into an array of tokens that correspond to each string
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


//the functions is_number and is_name were taken and modified from:
//https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c

/// Checks if a string is a number
/// note: does not accept '-' or '.' as part of a number
/// \param s string we want to check if it is a number
/// \return true if it is a number, false if it is not
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();\
    bool isDecimalNum = false;
    while (it != s.end()){
        //if it is a digit go to next char
        if(std::isdigit(*it));
        //if it is not a number check if it is a decimal point
        else if(*it == '.'){
            if(isDecimalNum){
                //we cannot have multiple decimals
                break;
            }
            else{
                //save the fact we have a decimal point
                isDecimalNum = true;
            }
        }
        else{
            //this is not a number or a decimal point
            break;
        }

        ++it;
    }
    //if we looped through the whole word without breaking, and it is not an empty word, we have a number
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
/// Note: END_TOKEN is considered a terminal
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

void Table::GenerateFirstSet() {

}

void Table::GenerateRules() {
    //rule 0
    std::vector<int> rule{EXPR_TOKEN};
    rules.insert({0, rule});

    //rule 1
    rule = {TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({1, rule});

    //rule 2
    rule = {PLUS_TOKEN, TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({2, rule});

    //rule 3
    rule = {MINUS_TOKEN, TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({3, rule});

    //rule 4 is epsilon so it is empty
    rule = {};
    rules.insert({4, rule});

    //rule 5
    rule = {FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({5, rule});

    //rule 6
    rule = {MULTIPLY_TOKEN, FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({6, rule});

    //rule 7
    rule = {DIVIDE_TOKEN, FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({7, rule});

    //rule 8 is epsilon
    rule = {};
    rules.insert({8, rule});

    //rule 9
    rule = {OPEN_PARAN_TOKEN, EXPR_TOKEN, CLOSE_PARAN_TOKEN};
    rules.insert({9, rule});

    //rule 10
    rule = {NUM_TOKEN};
    rules.insert({10, rule});

    //rule 11
    rule = {NAME_TOKEN};
    rules.insert({11, rule});

}

Table::Table() {
    GenerateRules();
    GenerateFirstSet();
    GenerateFollowSet();
}

void Table::GenerateFollowSet() {

}