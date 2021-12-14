//
// Created by Peter Simonson on 12/5/21.
//

#ifndef CS6820HW2_TOKENS_H
#define CS6820HW2_TOKENS_H

#include <vector>
#include <set>

///This contains all of the terminals and non-terminals in our grammar
///Note: non-terminals are list first. Terminals occur after NUM_OF_NON_TERMINALS enum
enum token{
    START_TOKEN,
    LINE_FULL_TOKEN,
    LINE_VAR_NAME,
    LINE_VAR_NAME_REMAINING,
    PROCEDURE_PARAMS_TOKEN,
    PROCEDURE_ARGS_TOKEN,
    PARAMS_TOKEN,
    ARGS_TOKEN,
    MORE_PARAMS_TOKEN,
    MORE_ARGS_TOKEN,
    EXPR_TOKEN,
    L_TERM_ADD_SUB_TOKEN,
    R_TERM_ADD_SUB_TOKEN,
    ADD_SUB_PRIME_TOKEN,
    L_TERM_MULT_DIV_TOKEN,
    R_TERM_MULT_DIV_TOKEN,
    MULT_DIV_PRIME_TOKEN,
    MULT_AND_RIGHT_OP_TOKEN,
    DIV_AND_RIGHT_OP_TOKEN,
    L_TERM_POWER_TOKEN,
    R_TERM_POWER_TOKEN,
    POWER_PRIME_TOKEN,
    POWER_AND_RIGHT_OP_TOKEN,
    G_FACTOR_TOKEN,
    PARENS_TOKEN,
    POSVAL_TOKEN,
    SPACE_NEG_VAL_TOKEN,
    VAR_TYPE_TOKEN,
    VAR_TYPE_AFTER_TOKEN,
    EXPR_WITHOUT_NAME_TOKEN,
    G_TERM_TOKEN,
    NAME_OR_PROCEDURE_TOKEN,
    //Define Columns of our table
    NUM_OF_NON_TERMINALS,
    END_TOKEN  = NUM_OF_NON_TERMINALS,
    PROCEDURE_TOKEN,
    COMMA_TOKEN,
    EQUALS_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    MULTIPLY_TOKEN,
    DIVIDE_TOKEN,
    POWER_TOKEN,
    OPEN_PAREN_TOKEN,
    CLOSE_PAREN_TOKEN,
    OPEN_CURLY_TOKEN,
    CLOSE_CURLY_TOKEN,
    NAME_TOKEN,
    NUM_TOKEN,
    STRING_TOKEN,
    SPACE_NEG_NAME_TOKEN,
    SPACE_NEG_NUM_TOKEN,
    NEG_NAME_TOKEN,
    NEG_NUM_TOKEN,
    DATA_TYPE_TOKEN,
    RETURN_TOKEN,
    PRINT_NUM_TOKEN,
    PRINT_ISH_TOKEN,
    PRINT_STRING_TOKEN,
    READ_NUM_TOKEN,
    EPSILON_TOKEN,
    NUM_OF_TOKENS,
    ERROR_TOKEN = -1
};

bool is_terminal(const int& token);
bool is_Value_Token(int token);
bool is_Print_Token(int token);
bool is_Read_Token(int token);
std::vector<int> removeEpsilonFromSet(std::vector<int> set);
std::vector<int> unionize_sets(const std::vector<int>& firstSet, const std::vector<int>& secondSet);
bool set_contains_epsilon(std::vector<int> set);

#endif //CS6820HW2_TOKENS_H
