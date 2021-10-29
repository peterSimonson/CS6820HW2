//
// Created by Peter Simonson on 10/18/21.
//

#include "Table.h"
#include <set>

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
    if(token >= COLUMN_OFFSET && token <= NUMBER_OF_TOKENS){
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
    //set to true when we are finished finding the set
    bool finishedFindingSet = false;

    //loop through all the tokens
    for(int CURRENT_TOKEN = 0; CURRENT_TOKEN <= NUMBER_OF_TOKENS; CURRENT_TOKEN++){
        //just add it
        if(is_terminal(CURRENT_TOKEN)){
            firstSet.insert({CURRENT_TOKEN, {CURRENT_TOKEN}});
        }
        //find the set
        else{
            firstSet.insert({CURRENT_TOKEN, {}});
        }
    }

    while(!finishedFindingSet){
        //hold whether we made a change in the for loop
        bool madeAChange = false;
        //loop through all the productions
        for(auto & production : rules){
            //find the left and right sides of our production
            std::vector<int> productionRHS = production.second.rightHandSide;
            int productionLHS = production.second.leftHandSide;
            auto beta_i = productionRHS.begin();
            //save the original first set for this production
            std::vector<int> originalSet = firstSet[productionLHS];

            //get the first production element without epsilon
            std::vector<int> rhs = removeEpsilonFromSet(firstSet[*beta_i]);

            //starts as one and k starts as the amount of production terms
            int i = 1, k = (int) productionRHS.size();
            //TODO: Figure out why I do not ever enter this loop yet find the correct result
            while(set_contains_epsilon(firstSet[*beta_i]) && i <= k - 1){
                //increment our counters
                i++;
                beta_i++;
                //unionize the sets
                rhs = unionize_sets(rhs, removeEpsilonFromSet(firstSet[*beta_i]));
            }

            //check if we need to add epsilon
            if(i == k && set_contains_epsilon(firstSet[productionRHS[k - 1]])){
                rhs = unionize_sets(rhs, {EPSILON_TOKEN});
            }
            //update the set
            firstSet[productionLHS] = unionize_sets(firstSet[productionLHS], rhs);

            if(originalSet != firstSet[productionLHS]){
                madeAChange = true;
            }
        }
        //if we made a change do another loop
        finishedFindingSet = !madeAChange;
    }
}

void Table::GenerateRules() {
    //rule 0
    std::vector<int> rhs{EXPR_TOKEN};
    rules.insert({0, {START_TOKEN, rhs}});

    //rule 1
    rhs = {TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({1, {EXPR_TOKEN, rhs}});

    //rule 2
    rhs = {PLUS_TOKEN, TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({2, {EXPR_PRIME_TOKEN, rhs}});

    //rule 3
    rhs = {MINUS_TOKEN, TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({3, {EXPR_PRIME_TOKEN, rhs}});

    //rule 4
    rhs = {EPSILON_TOKEN};
    rules.insert({4, {EXPR_PRIME_TOKEN, rhs}});

    //rule 5
    rhs = {FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({5, {TERM_TOKEN, rhs}});

    //rule 6
    rhs = {MULTIPLY_TOKEN, FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({6, {TERM_PRIME_TOKEN, rhs}});

    //rule 7
    rhs = {DIVIDE_TOKEN, FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({7, {TERM_PRIME_TOKEN, rhs}});

    //rule 8
    rhs = {EPSILON_TOKEN};
    rules.insert({8, {TERM_PRIME_TOKEN, rhs}});

    //rule 9
    rhs = {OPEN_PARAN_TOKEN, EXPR_TOKEN, CLOSE_PARAN_TOKEN};
    rules.insert({9, {FACTOR_TOKEN, rhs}});

    //rule 10
    rhs = {NUM_TOKEN};
    rules.insert({10, {FACTOR_TOKEN, rhs}});

    //rule 11
    rhs = {NAME_TOKEN};
    rules.insert({11, {FACTOR_TOKEN, rhs}});

}

Table::Table() {
    GenerateRules();
    GenerateFirstSet();
    GenerateFollowSet();
}

void Table::GenerateFollowSet() {

}

/// Removes epsilon from a set if it exists in the set
/// \param set the set of integers you wish to remove EPSILON_TOKEN from
/// \return set without EPSILON_TOKEN
std::vector<int> removeEpsilonFromSet(std::vector<int> set){
    //remove epsilon token from the set if it exists
    set.erase(std::remove(set.begin(), set.end(), EPSILON_TOKEN), set.end());
    return set;
}

/// check if a set contains EPSILON_TOKEN
/// \param set the vector of ints you wish to check for EPSILON_TOKEN
/// \return return true if EPSILON_TOKEN is found. otherwise, return false
bool set_contains_epsilon(std::vector<int> set){
    if(std::find(set.begin(), set.end(), EPSILON_TOKEN) != set.end()){
        return true;
    }
    else{
        return false;
    }
}

/// Finds the union of two int vectors
/// \param firstSet vector of ints you wish to union with secondSet
/// \param secondSet vector of ints you wish to union with firstSet
/// \return a vector of sorted unionized tokens
std::vector<int> unionize_sets(const std::vector<int>& firstSet, const std::vector<int>& secondSet){
    std::set<int> all;
    //add everything from the first set
    for(auto & token : firstSet){
        all.insert(token);
    }
    //add everything from second set
    for(auto & token : secondSet){
        all.insert(token);
    }

    return {all.begin(), all.end()};
}
