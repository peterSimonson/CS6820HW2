//
// Created by Peter Simonson on 10/18/21.
//

#include "Table.h"
#include <algorithm>
#include <stdexcept>

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
    for(int CURRENT_TOKEN = 0; CURRENT_TOKEN < NUM_OF_TOKENS; CURRENT_TOKEN++){
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
    
    rules.insert({(int)rules.size(), {lhs, rhs}});
}
///Generates the production rules for our language
void Table::GenerateRules() {
    addRule(START_TOKEN, {LINE_FULL_TOKEN});//0
    addRule(LINE_FULL_TOKEN, {DATA_TYPE_TOKEN, VAR_TYPE_AFTER_TOKEN});
    addRule(LINE_FULL_TOKEN, {LINE_VAR_NAME});
    addRule(LINE_FULL_TOKEN, {EXPR_WITHOUT_NAME_TOKEN});
    addRule(LINE_FULL_TOKEN, {RETURN_TOKEN, G_TERM_TOKEN});
    addRule(LINE_FULL_TOKEN, {CLOSE_CURLY_TOKEN});
    addRule(PRINT_NUM_TOKEN, {NAME_TOKEN});
    addRule(PRINT_ISH_TOKEN, {NAME_TOKEN});
    addRule(PRINT_STRING_TOKEN, {STRING_TOKEN});
    addRule(VAR_TYPE_AFTER_TOKEN, {LINE_VAR_NAME});
    addRule(VAR_TYPE_AFTER_TOKEN, {PROCEDURE_TOKEN, NAME_TOKEN, PROCEDURE_PARAMS_TOKEN, OPEN_CURLY_TOKEN});
    addRule(LINE_VAR_NAME, {NAME_TOKEN, LINE_VAR_NAME_REMAINING});
    addRule(LINE_VAR_NAME_REMAINING, {EQUALS_TOKEN, EXPR_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {POWER_AND_RIGHT_OP_TOKEN, MULT_DIV_PRIME_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {MULT_AND_RIGHT_OP_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {DIV_AND_RIGHT_OP_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(LINE_VAR_NAME_REMAINING, {ADD_SUB_PRIME_TOKEN});
    addRule(EXPR_WITHOUT_NAME_TOKEN, {NUM_TOKEN, POWER_PRIME_TOKEN, MULT_DIV_PRIME_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(EXPR_WITHOUT_NAME_TOKEN, {NEG_NUM_TOKEN, POWER_PRIME_TOKEN, MULT_DIV_PRIME_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(EXPR_WITHOUT_NAME_TOKEN, {PARENS_TOKEN, POWER_PRIME_TOKEN, MULT_DIV_PRIME_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(PROCEDURE_PARAMS_TOKEN, {OPEN_PAREN_TOKEN, PARAMS_TOKEN, CLOSE_PAREN_TOKEN});
    addRule(PARAMS_TOKEN, {DATA_TYPE_TOKEN, NAME_TOKEN, MORE_PARAMS_TOKEN});
    addRule(PARAMS_TOKEN, {EPSILON_TOKEN});
    addRule(MORE_PARAMS_TOKEN, {COMMA_TOKEN, DATA_TYPE_TOKEN, NAME_TOKEN, MORE_PARAMS_TOKEN});
    addRule(MORE_PARAMS_TOKEN, {EPSILON_TOKEN});
    addRule(EXPR_TOKEN, {L_TERM_ADD_SUB_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(L_TERM_ADD_SUB_TOKEN, {L_TERM_MULT_DIV_TOKEN, MULT_DIV_PRIME_TOKEN});
    addRule(L_TERM_MULT_DIV_TOKEN, {L_TERM_POWER_TOKEN, POWER_PRIME_TOKEN});
    addRule(R_TERM_ADD_SUB_TOKEN, {R_TERM_MULT_DIV_TOKEN, MULT_DIV_PRIME_TOKEN});
    addRule(R_TERM_MULT_DIV_TOKEN, {R_TERM_POWER_TOKEN, POWER_PRIME_TOKEN});
    addRule(ADD_SUB_PRIME_TOKEN, {PLUS_TOKEN, R_TERM_ADD_SUB_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(ADD_SUB_PRIME_TOKEN, {MINUS_TOKEN, R_TERM_ADD_SUB_TOKEN, ADD_SUB_PRIME_TOKEN});
    addRule(ADD_SUB_PRIME_TOKEN, {EPSILON_TOKEN});
    addRule(MULT_DIV_PRIME_TOKEN, {MULT_AND_RIGHT_OP_TOKEN});
    addRule(MULT_DIV_PRIME_TOKEN, {DIV_AND_RIGHT_OP_TOKEN});
    addRule(MULT_DIV_PRIME_TOKEN, {EPSILON_TOKEN});
    addRule(MULT_AND_RIGHT_OP_TOKEN, {MULTIPLY_TOKEN, R_TERM_MULT_DIV_TOKEN, MULT_DIV_PRIME_TOKEN});
    addRule(DIV_AND_RIGHT_OP_TOKEN, {DIVIDE_TOKEN, R_TERM_MULT_DIV_TOKEN, MULT_DIV_PRIME_TOKEN});
    addRule(POWER_PRIME_TOKEN, {POWER_AND_RIGHT_OP_TOKEN});
    addRule(POWER_PRIME_TOKEN, {EPSILON_TOKEN});
    addRule(POWER_AND_RIGHT_OP_TOKEN, {POWER_TOKEN, R_TERM_POWER_TOKEN, POWER_PRIME_TOKEN});
    addRule(L_TERM_POWER_TOKEN, {G_TERM_TOKEN});
    addRule(L_TERM_POWER_TOKEN, {NEG_NUM_TOKEN});
    addRule(L_TERM_POWER_TOKEN, {NEG_NAME_TOKEN});
    addRule(R_TERM_POWER_TOKEN, {G_TERM_TOKEN});
    addRule(G_TERM_TOKEN, {PARENS_TOKEN});
    addRule(G_TERM_TOKEN, {NUM_TOKEN});
    addRule(G_TERM_TOKEN, {SPACE_NEG_VAL_TOKEN});
    addRule(NAME_OR_PROCEDURE_TOKEN, {NAME_TOKEN, ARGS_TOKEN});
    addRule(ARGS_TOKEN, {OPEN_PAREN_TOKEN, EXPR_TOKEN, MORE_ARGS_TOKEN, CLOSE_PAREN_TOKEN});
    addRule(ARGS_TOKEN, {EPSILON_TOKEN});
    addRule(MORE_ARGS_TOKEN, {COMMA_TOKEN, EXPR_TOKEN, MORE_ARGS_TOKEN});
    addRule(MORE_ARGS_TOKEN, {EPSILON_TOKEN});
    addRule(PARENS_TOKEN, {OPEN_PAREN_TOKEN, EXPR_TOKEN, CLOSE_PAREN_TOKEN});
}

///Generates the data for our language needed to parse expressions
Table::Table() {
    //add our built-in data types
    dataTypes = {"ish", "num"};
    //initiate the global scope
    AddVariableScope();
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
                            throw std::logic_error(errorMessage);
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
    //loop through the current variable scopes
    for(auto & currentScope : variableScopes){
        //loop through all the variables in the current scope
        for(auto & variable : currentScope){
            //if we have a variable with the name it is already declared
            if(nameOfVariable == variable->name){
                return true;
            }
        }
    }
    return false;
}

/// Get the variable corresponding to the name you just passed
/// \param nameOfVariableToReturn the name of the variable you want to get
/// \return The variable corresponding to the name you entered. Throws an exception if their is no variable by that name
std::shared_ptr<VariableNode> Table::GetVariable(const std::string &nameOfVariableToReturn) {
    std::shared_ptr<VariableNode> varToReturn = nullptr;

    for(auto & currentScope : variableScopes){
        //loop through all the variables in the current scope
        for(auto & variable : currentScope){
            if(nameOfVariableToReturn == variable->name){
                varToReturn = variable;
                break;
            }
        }
    }

    //we couldn't find a match so through an error
    if(varToReturn == nullptr){
        throw std::logic_error(nameOfVariableToReturn + " is an undeclared or out of scope variable being referenced\n");
    }

    return varToReturn;
}

/// Add a variable to the list of declared variables
/// Note: this function checks if there is already a variable by the same name
/// \param varToAdd the variable you wish to declare
/// \return True if we added the variable. False if we were unable to add the variable
bool Table::AddVariable(const std::shared_ptr<VariableNode>& varToAdd) {
    bool notPreviouslyAVar = !is_already_a_var(varToAdd->name);
    //if the variable name is not already used add it to the variables
    if(notPreviouslyAVar){
        //get the current scope and add a new variable
        variableScopes.back().push_back(varToAdd);
    }

    return notPreviouslyAVar;
}

void Table::AddVariableScope() {
    variableScopes.emplace_back();
}

void Table::RemoveVariableScope() {
    variableScopes.pop_back();
}

bool Table::AddProcedure(const ProcedureNode &procedureToAdd) {
    //check to make sure we do not have any matching procedures
    for(auto & procedure : procedures){

        //get the names of the new and old procedures
        std::string newProcedureName = procedureToAdd.name;
        std::string oldProcedureName = procedure->name;

        //get the number of parameters for each procedure
        int newProcedureParamsSize = (int)procedureToAdd.parameters.size();
        int oldProcedureParamsSize = (int)procedure->parameters.size();

        //if the names match, and we have the same number of parameters
        if(oldProcedureName == newProcedureName && oldProcedureParamsSize == newProcedureParamsSize){
            //holds whether all the parameter types match
            bool paramsMatch = true;

            //loop through to ensure all the params do not match
            for(int paramIndex = 0; paramIndex != procedure->parameters.size(); paramIndex++){
                std::string newParamType = procedureToAdd.parameters[paramIndex]->type;
                std::string oldParamType = procedure->parameters[paramIndex]->type;

                //if at any point the params datatype does not match we can stop checking
                if(oldParamType != newParamType){
                    paramsMatch = false;
                    break;
                }
            }
            //at this point the name and all the params match, so we cannot declare a new function
            if(paramsMatch){
                return false;
            }
        }
    }

    procedures.push_back(std::make_shared<ProcedureNode>(procedureToAdd));
    return true;
}

void Table::CleanUpTable() {
    //clean up variable scopes
    for(auto it = variableScopes.begin(); it != variableScopes.end(); it++){
        RemoveVariableScope();
    }

}

std::shared_ptr<ProcedureNode> Table::GetProcedure(const std::string &nameOfProcedureToReturn,
                                                   const std::vector<std::shared_ptr<TreeNode>>& functionArguments) {

    for(auto & procedure : procedures){
        //check if the procedure name matches and the number of arguments match
        if(procedure->name == nameOfProcedureToReturn && functionArguments.size() == procedure->parameters.size()){
            //TODO: actually check variable type
            return std::make_shared<ProcedureNode>(*procedure);
        }
    }

    //we couldn't find a match so through an error

    throw std::logic_error(nameOfProcedureToReturn + " is an undeclared procedure being referenced\n");

}