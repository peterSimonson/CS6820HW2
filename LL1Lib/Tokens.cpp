//
// Created by Peter Simonson on 12/8/21.
//

#include "Tokens.h"

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

bool is_Value_Token(int token){
    if(token >= CLOSE_PAREN_TOKEN && token <= NEG_NUM_TOKEN){
        return true;
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
    if(token >= NUM_OF_NON_TERMINALS && token < NUM_OF_TOKENS){
        return true;
    }
    else{
        return false;
    }
}

bool is_Print_Token(int token) {
    if(token >= PRINT_NUM_TOKEN && token <= PRINT_STRING_TOKEN){
        return true;
    }
    else{
        return false;
    }
}

bool is_Read_Token(int token) {
    if(token == READ_NUM_TOKEN){
        return true;
    }
    else{
        return false;
    }
}
