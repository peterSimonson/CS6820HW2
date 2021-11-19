//
// Created by Peter Simonson on 10/18/21.
//

#include "Table.h"
#include <set>
#include <algorithm>
#include <iostream>

//the functions is_number and is_name were taken and modified from:
//https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c

/// Checks if a string is a number
/// note: does not accept negative numbers
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

/// Check if a number is a decimal or not
/// Note: the string must have returned true from is_number
/// \param number string containing a number
/// \return true if the number is a decimal number. false if it is an integer
bool is_decimal_number(const std::string& number){
    if(number.find('.') != std::string::npos){
        return true;
    }
    else{
        return false;
    }
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

/// Check if the string is a datatype
/// \param word string you want to check if it is a datatype
/// \param dataTypes the list of data types the user can declare
/// \return true if word matches one of the data types. Otherwise, we return false.
bool is_data_type(const std::string& word, const std::vector<std::string>& dataTypes){

    if(std::find(dataTypes.begin(), dataTypes.end(), word) != dataTypes.end()){
        //if we find a match return true
        return true;
    }
    else{
        //otherwise, return false
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

/// Creates the first set for our language
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

void Table::addRule(int lhs, std::vector<int>&& rhs){
    
    rules.insert({rules.size(), {lhs, rhs}}); 
}
///Generates the production rules for our language
void Table::GenerateRules() {
    addRule(START_TOKEN,             {LINE_FULL_TOKEN});
    addRule(LINE_FULL_TOKEN,         {VAR_TYPE, LINE_VAR_NAME});
    addRule(LINE_FULL_TOKEN,         {LINE_VAR_NAME});
    addRule(LINE_FULL_TOKEN,         {NUM_TOKEN, POWER_PRIME_TOKEN, MULTDIV_PRIME_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(LINE_FULL_TOKEN,         {NEG_NUM_TOKEN, POWER_PRIME_TOKEN, MULTDIV_PRIME_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(LINE_FULL_TOKEN,         {PARENS_EXPR_TOKEN});
    //addRule(LINE_FULL_TOKEN,         {
    addRule(LINE_VAR_NAME,           {NAME_TOKEN, LINE_VAR_NAME_REMAINING});
    addRule(LINE_VAR_NAME_REMAINING, {EQUALS_TOKEN, EXPR_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {POWER_AND_RIGHTOP_TOKEN, MULTDIV_PRIME_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {MULT_AND_RIGHTOP_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {DIV_AND_RIGHTOP_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {ADDSUB_PRIME_TOKEN});
    addRule(VAR_TYPE,                {DATA_TYPE_TOKEN});
    addRule(EXPR_TOKEN,              {L_TERM_ADDSUB_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(L_TERM_ADDSUB_TOKEN,     {L_TERM_MULTDIV_TOKEN, MULTDIV_PRIME_TOKEN});
    addRule(L_TERM_MULTDIV_TOKEN,    {L_TERM_POWER_TOKEN, POWER_PRIME_TOKEN});    
    addRule(R_TERM_ADDSUB_TOKEN,     {R_TERM_MULTDIV_TOKEN, MULTDIV_PRIME_TOKEN});
    addRule(R_TERM_MULTDIV_TOKEN,    {R_TERM_POWER_TOKEN, POWER_PRIME_TOKEN});
    addRule(ADDSUB_PRIME_TOKEN,      {PLUS_TOKEN, R_TERM_ADDSUB_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(ADDSUB_PRIME_TOKEN,      {MINUS_TOKEN, R_TERM_ADDSUB_TOKEN, ADDSUB_PRIME_TOKEN});
    addRule(ADDSUB_PRIME_TOKEN,      {EPSILON_TOKEN});
    addRule(MULTDIV_PRIME_TOKEN,     {MULT_AND_RIGHTOP_TOKEN});
    addRule(MULTDIV_PRIME_TOKEN,     {DIV_AND_RIGHTOP_TOKEN});
    addRule(MULTDIV_PRIME_TOKEN,     {EPSILON_TOKEN});
    addRule(POWER_PRIME_TOKEN,       {POWER_AND_RIGHTOP_TOKEN});
    addRule(POWER_PRIME_TOKEN,       {EPSILON_TOKEN});
    addRule(MULT_AND_RIGHTOP_TOKEN,  {MULTIPLY_TOKEN, R_TERM_MULTDIV_TOKEN, MULTDIV_PRIME_TOKEN});
    addRule(DIV_AND_RIGHTOP_TOKEN,   {DIVIDE_TOKEN, R_TERM_MULTDIV_TOKEN, MULTDIV_PRIME_TOKEN});
    addRule(POWER_AND_RIGHTOP_TOKEN, {POWER_TOKEN, R_TERM_POWER_TOKEN, POWER_PRIME_TOKEN});
    addRule(L_TERM_POWER_TOKEN,      {G_FACTOR_TOKEN});
    addRule(L_TERM_POWER_TOKEN,      {NEG_NUM_TOKEN});
    addRule(L_TERM_POWER_TOKEN,      {NEG_NAME_TOKEN});
    addRule(R_TERM_POWER_TOKEN,      {G_FACTOR_TOKEN});
    addRule(G_FACTOR_TOKEN,          {PARENS_EXPR_TOKEN});
    addRule(G_FACTOR_TOKEN,          {POSVAL_TOKEN});
    addRule(G_FACTOR_TOKEN,          {SPACE_NEG_VAL_TOKEN});
    addRule(PARENS_EXPR_TOKEN,       {OPEN_PARAN_TOKEN, EXPR_TOKEN, CLOSE_PARAN_TOKEN});
    addRule(POSVAL_TOKEN,            {NUM_TOKEN});
    addRule(POSVAL_TOKEN,            {NAME_TOKEN});
    addRule(SPACE_NEG_VAL_TOKEN,     {SPACE_NEG_NUM_TOKEN});
    addRule(SPACE_NEG_VAL_TOKEN,     {SPACE_NEG_NAME_TOKEN});
}

///Generates the data for our language needed to parse expressions
Table::Table() {
    //add our built-in data types
    dataTypes = {"ish", "num"};
    GenerateRules();
    GenerateFirstSet();
    GenerateFollowSet();
    //Note: we are not building first+ set. Instead, we use the function findFirstPlusSet
    BuildTable();
}

///Creates the follow set. Note: This function requires that the first set has already been generated
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

///Build the table once you have generated first and follow set. note: we use findFirstPlusSet for the first plus set
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
                        //if we have the default error token we can write to this cell of the table
                        if(RuleTable[terminal - NUM_OF_NON_TERMINALS][A] == ERROR_TOKEN){
                            RuleTable[terminal - NUM_OF_NON_TERMINALS][A] = ruleNumber;
                        }
                        //else there is a previously initialized variable which we are overwriting
                        else{
                            //THIS IS UNACCEPTABLE!
                            std::string errorMessage = "Value of (" + std::to_string(terminal)
                                    + "," + std::to_string(A) + ") is already " +
                                    std::to_string(RuleTable[terminal - NUM_OF_NON_TERMINALS][A]) +
                                    " but you are trying to change it to " + std::to_string(ruleNumber) + "\n";
                            //throw std::logic_error(errorMessage);
                            std::cout << errorMessage;
                            RuleTable[terminal - NUM_OF_NON_TERMINALS][A] = ruleNumber;
                        }

                    }
                }
            }
        }
    }
}

/// Finds the first plus set. This requires first and follow set have already been generated
/// \param production the production you wish to find the first plus set for
/// \return the tokens in the first plus set for production
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

/// Checks if string corresponds to an already declared variable name
/// \param nameOfVariable The name you wish to check
/// \return True if a variable has that name. False if their is no variable with the name
bool Table::is_already_a_var(const std::string& nameOfVariable) {

    for(auto & variable : variables){
        if(nameOfVariable == variable.variableName){
            return true;
        }
    }
    return false;
}

/// Get the variable corresponding to the name you just passed
/// \param nameOfVariableToReturn the name of the variable you want to get
/// \return The variable corresponding to the name you entered. Returns nullptr if their is no variable by that name
VariableNode * Table::GetVariable(const std::string &nameOfVariableToReturn) {
    VariableNode *varToReturn = nullptr;
    for(auto & variable : variables){
        if(nameOfVariableToReturn == variable.variableName){
            varToReturn = &variable;
            break;
        }
    }
    return varToReturn;
}

/// Add a variable to the list of declared variables
/// Note: this function checks if there is already a variable by the same name
/// \param varToAdd the variable you wish to declare
/// \return True if we added the variable. False if we were unable to add the variable
bool Table::AddVariable(const VariableNode& varToAdd) {
    bool isNotCurrentlyAVar = !is_already_a_var(varToAdd.variableName);
    //if the variable name is not already used add it to the variables
    if(isNotCurrentlyAVar){
        variables.push_back(varToAdd);
    }

    return isNotCurrentlyAVar;
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
