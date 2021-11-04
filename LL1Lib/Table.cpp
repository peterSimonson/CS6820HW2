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

    for(str = words.begin(); str != words.end(); str++){
        std::string word = *str;
        //check what type of token this is
        if(is_number(word)){
            tokens.push_back(NUM_TOKEN);
        }
        else if(is_name(word)){
            tokens.push_back(NAME_TOKEN);
        }
        //if the first char is a space check if everything else is a num
        else if(word.at(0) == ' ' && is_Neg_Num(word.substr(1, word.size()))){
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NUM_TOKEN);
            }
            else{
                tokens.push_back(SPACE_NEG_NUM_TOKEN);
            }
        }
        //if the first char is a space check if everything else is a name
        else if(word.at(0) == ' ' && is_Neg_Name(word.substr(1, word.size()))){
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NAME_TOKEN);
            }
            else{
                tokens.push_back(SPACE_NEG_NAME_TOKEN);
            }
        }
        //if the first char is a space check if everything else is a num
        else if(word.at(0) == '-' && is_number(word.substr(1, word.size()))){
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NUM_TOKEN);
            }
            else{
                tokens.push_back(NEG_NUM_TOKEN);
            }
        }
        //if the first char is a space check if everything else is a name
        else if(word.at(0) == '-' && is_name(word.substr(1, word.size()))){
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NAME_TOKEN);
            }
            else{
                tokens.push_back(NEG_NAME_TOKEN);
            }
        }
        else if(word == "+"){
            tokens.push_back(PLUS_TOKEN);
        }
        else if(word == "-" || word == " -"){
            tokens.push_back(MINUS_TOKEN);
        }
        else if(word == "*"){
            tokens.push_back(MULTIPLY_TOKEN);
        }
        else if(word == "/"){
            tokens.push_back(DIVIDE_TOKEN);
        }
        else if(word == "("){
            tokens.push_back(OPEN_PARAN_TOKEN);
        }
        else if(word == ")"){
            tokens.push_back(CLOSE_PARAN_TOKEN);
        }
        //if we could not find a match than push an error token
        else{
            tokens.push_back(ERROR_TOKEN);
        }
    }

    //push the end of file to the end of the vector
    tokens.push_back(END_TOKEN);

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
    std::string::const_iterator it = s.begin();
    bool isDecimalNum = false;

    //first char must be a digit
    if(!std::isdigit(*it)){
        return false;
    }
    it++;

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
        while (it != s.end() && (std::isalnum(*it)) || *it == '_') ++it;
        return !s.empty() && it == s.end();
    }
    else{
        return false;
    }

}

bool is_Neg_Num(const std::string& s){
    if(s.at(0) == '-' && is_number(s.substr(1, s.size()))){
        return true;
    }
    else{
        return false;
    }
}

bool is_Neg_Name(const std::string& s){
    if(s.at(0) == '-' && is_name(s.substr(1, s.size()))){
        return true;
    }
    else{
        return false;
    }
}

bool is_Value_Token(int token){
    if(token >= CLOSE_PARAN_TOKEN && token <=NEG_NUM_TOKEN){
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
    if(token >= NUM_OF_NON_TERMINALS && token <= NUM_OF_TOKENS){
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
    return RuleTable[column - NUM_OF_NON_TERMINALS][row];
}

void Table::GenerateFirstSet() {
    //set to true when we are finished finding the set
    bool finishedFindingSet = false;

    //loop through all the tokens
    for(int CURRENT_TOKEN = 0; CURRENT_TOKEN <= NUM_OF_TOKENS; CURRENT_TOKEN++){
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
            std::vector<int> rhs = removeEpsilonFromSet(firstSet[productionRHS.front()]);

            //starts as one and k starts as the amount of production terms
            int i = 1 , k = (int) productionRHS.size();
            //TODO: Figure out why I do not ever enter this loop yet find the correct result
            //I think I need to loop through all the betas
            for(int ii = 0; ii < k - 1; ii++){
                if(set_contains_epsilon(firstSet[productionRHS[ii]]) && i <= k){
                    unionize_sets(rhs, removeEpsilonFromSet(firstSet[productionRHS[ii+1]]));
                    i++;
                }
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
    //          productNum      productLHS   productRHS
    rules.insert({0, {START_TOKEN, rhs}});

    //rule 1
    rhs = {L_TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({1, {EXPR_TOKEN, rhs}});

    //rule 2
    rhs = {L_FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({2, {L_TERM_TOKEN, rhs}});

    //rule 3
    rhs = {R_FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({3, {R_TERM_TOKEN, rhs}});

    //rule 4
    rhs = {PLUS_TOKEN, R_TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({4, {EXPR_PRIME_TOKEN, rhs}});

    //rule 5
    rhs = {MINUS_TOKEN, R_TERM_TOKEN, EXPR_PRIME_TOKEN};
    rules.insert({5, {EXPR_PRIME_TOKEN, rhs}});

    //rule 6
    rhs = {EPSILON_TOKEN};
    rules.insert({6, {EXPR_PRIME_TOKEN, rhs}});

    //rule 7
    rhs = {MULTIPLY_TOKEN, R_FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({7, {TERM_PRIME_TOKEN, rhs}});

    //rule 8
    rhs = {DIVIDE_TOKEN, R_FACTOR_TOKEN, TERM_PRIME_TOKEN};
    rules.insert({8, {TERM_PRIME_TOKEN, rhs}});

    //rule 9
    rhs = {EPSILON_TOKEN};
    rules.insert({9, {TERM_PRIME_TOKEN, rhs}});

    //rule 10
    rhs = {G_FACTOR_TOKEN};
    rules.insert({10, {L_FACTOR_TOKEN, rhs}});

    //rule 11
    rhs = {NEG_NUM_TOKEN};
    rules.insert({11, {L_FACTOR_TOKEN, rhs}});

    //rule 12
    rhs = {NEG_NAME_TOKEN};
    rules.insert({12, {L_FACTOR_TOKEN, rhs}});

    //rule 13
    rhs = {G_FACTOR_TOKEN};
    rules.insert({13, {R_FACTOR_TOKEN, rhs}});

    //rule 14
    rhs = {OPEN_PARAN_TOKEN, EXPR_TOKEN, CLOSE_PARAN_TOKEN};
    rules.insert({14, {G_FACTOR_TOKEN, rhs}});

    //rule 15
    rhs = {POSVAL_TOKEN};
    rules.insert({15, {G_FACTOR_TOKEN, rhs}});

    //rule 16
    rhs = {SPACE_NEG_VAL_TOKEN};
    rules.insert({16, {G_FACTOR_TOKEN, rhs}});

    //rule 17
    rhs = {NUM_TOKEN};
    rules.insert({17, {POSVAL_TOKEN, rhs}});

    //rule 18
    rhs = {NAME_TOKEN};
    rules.insert({18, {POSVAL_TOKEN, rhs}});

    //rule 19
    rhs = {SPACE_NEG_NUM_TOKEN};
    rules.insert({19, {SPACE_NEG_VAL_TOKEN, rhs}});

    //rule 20
    rhs = {SPACE_NEG_NAME_TOKEN};
    rules.insert({20, {SPACE_NEG_VAL_TOKEN, rhs}});
}

Table::Table() {
    GenerateRules();
    GenerateFirstSet();
    GenerateFollowSet();
    //Note: we are not building first+ set. Instead, we use the function findFirstPlusSet
    BuildTable();
}

void Table::GenerateFollowSet() {
    //loop through the non-terminals
    for (int currentToken = START_TOKEN; currentToken < NUM_OF_NON_TERMINALS; currentToken++){
        //add an empty entry for each non-terminal
        followSet.insert({currentToken, {}});
    }

    //add END_TOKEN to the start token
    followSet[START_TOKEN] = {END_TOKEN};

    //set to true when we are finished finding the set
    bool finishedFindingSet = false;

    //keep on looping until we are finished finding the follow set
    while(!finishedFindingSet){
        //hold whether we made a change in the for loop
        bool madeAChange = false;

        //loop through all the productions
        for(auto & production : rules){
            //find the left and right sides of our production
            std::vector<int> productionRHS = production.second.rightHandSide;
            int productionLHS = production.second.leftHandSide;
            auto beta_i = productionRHS.rbegin();

            std::vector<int> trailer = followSet[productionLHS];
            for(int k = (int) productionRHS.size(); k >= 1; k--){
                if(!is_terminal(*beta_i)){
                    std::vector<int> originalSet = followSet[*beta_i];
                    followSet[*beta_i] = unionize_sets(originalSet, trailer);

                    if(set_contains_epsilon(firstSet[*beta_i])){
                        trailer = unionize_sets(trailer, removeEpsilonFromSet(firstSet[*beta_i]));
                    }
                    else{
                        trailer = firstSet[*beta_i];
                    }
                    //check if we made a change
                    if(originalSet != followSet[*beta_i]){
                        madeAChange = true;
                    }
                }
                else{
                    trailer = firstSet[*beta_i];
                }
                beta_i++;
            }
        }

        //if we did not make any changes we can exit the while loop
        finishedFindingSet = !madeAChange;
    }
}

void Table::BuildTable(){
    //loop through the non-terminals
    for(int A = START_TOKEN; A < NUM_OF_NON_TERMINALS; A++){
        //fill the table completely with error tokens
        for(int w = START_TOKEN; w < NUM_OF_TOKENS - NUM_OF_NON_TERMINALS; w++){
            RuleTable[w][A] = ERROR_TOKEN;
        }
        //loop through all the productions
        for(auto & ruleEntry : rules){
            //get the rule number and the production
            rule productionRule = ruleEntry.second;
            int ruleNumber = ruleEntry.first;
            if(productionRule.leftHandSide == A){
                std::vector<int> firstPlusSet = findFirstPlusSet(productionRule);
                //first plus should only have terminals in it
                for(auto & terminal : firstPlusSet){
                    if(terminal!= EPSILON_TOKEN){
                        RuleTable[terminal - NUM_OF_NON_TERMINALS][A] = ruleNumber;
                    }
                }
            }
        }
    }
}

std::vector<int> Table::findFirstPlusSet(rule production){
    //find the first beta on the right-hand side of the production
    int beta_1 = production.rightHandSide.front();
    //find A on left-hand side of the production
    int A = production.leftHandSide;
    //check if beta_1 contains epsilon
    if(!set_contains_epsilon(firstSet[beta_1])){
        //if it does not return the first set for beta_1
        return firstSet[beta_1];
    }
    //otherwise, union the first of beta_1 with the front of alpha
    else{
        return unionize_sets(followSet[A], firstSet[beta_1]);
    }
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
