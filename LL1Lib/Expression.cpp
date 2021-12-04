//
// Created by Peter Simonson on 11/11/21.
//

#include <stack>
#include <algorithm>
#include "Expression.h"
#include "Nodes.h"
#include <stdexcept>

/// function to find the precedence level of an operator. Taken from: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
/// \param operation check the precedence of the operator
/// \return
int precedenceOfOperator(std::string operation)
{
    switch (operation.at(0))
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

/// Converts the infix vector of strings in text into a post-fix vector of string
/// Function was taken and modified from: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
/// \return post-fix vector of strings created from strings in text
std::vector<std::string> convertInfixToPostFix(const std::vector<std::string>& infixExpression) {
    std::vector<std::string> postFixExpression;
    std::vector<std::string> stack;

    //loop through the remaining words
    for(auto word = infixExpression.begin(); word!= infixExpression.end(); word++){

        //if it is a variable of a function call
        if(is_name(*word)){
            std::string wordToPush = *word;
            //if the next word is an open parenthesis we have a function call
            if(*(word + 1) == "("){
                //add the rest of the function call to the word to push back
                word++;
                //while we don't hit the close parenthesis
                while(*word != ")"){
                    //add the word
                    wordToPush += *word;
                    word++;
                }
                //add the close parenthesis
                wordToPush += *word;
            }
            postFixExpression.push_back(wordToPush);
        }
        //if it is a number push it back of the stack
        else if(is_number(*word)){
            postFixExpression.push_back(*word);
        }
            //add the open paran to the stack. We will look for it once we encounter the close paran
        else if(*word == "("){
            stack.push_back(*word);
        }
            //if we have a closing paran look for all teh operators before the open paran
        else if(*word == ")"){
            while(!stack.empty() && stack.back() != "("){
                //add the operator to the postfix expression
                postFixExpression.push_back(stack.back());
                stack.pop_back();
            }
            //remove the open paran
            stack.pop_back();
        }
            //else we have an operator
        else{
            int precedenceOfWord = precedenceOfOperator(*word);
            //take all operators off the stack that have a precedence equal to or greater than word
            while(!stack.empty() && precedenceOfWord <= precedenceOfOperator(stack.back())){
                postFixExpression.push_back(stack.back());
                stack.pop_back();
            }
            //put word onto the stack
            stack.push_back(*word);
        }
    }

    //take all remaining operators off the stack
    while(!stack.empty()){
        postFixExpression.push_back(stack.back());
        stack.pop_back();
    }

    return postFixExpression;
}

/// Evaluates a postfix expression
/// \param postFixExpression the post-fix expression you wish to evaluate
/// \return the value of the post-fix expression
std::shared_ptr<TreeNode> evaluatePostFix(const std::vector<std::string> &postFixExpression, Table table) {

    //holds the stack needed to evaluate
    std::stack<std::shared_ptr<TreeNode>> stack;
    //loop through each term in the post-fix expression
    for(auto & word : postFixExpression){
        //if word is a number, create an int node and push it to the stack
        if(is_number(word)){
            if(is_decimal_number(word)){
                std::shared_ptr<TreeNode> decimalNode(new DecimalNode(std::stod(word)));
                stack.push(std::move(decimalNode));
            }
            //if it isn't a decimal it is an integer
            else{
                std::shared_ptr<TreeNode> intNode(new IntegerNode(std::stoi(word)));
                stack.push(std::move(intNode));
            }

        }
        //if it is a variable
        else if(is_name(word)){
            std::shared_ptr<TreeNode> nodeToPush;
            //if it is a negative variable
            if(is_Neg_Name(word)){
                //get the variable name without the minus sign
                std::shared_ptr<VariableNode> variableNode = table.GetVariable(word.substr(1, word.size()));
                //add the negative of variable node
                nodeToPush =  std::make_shared<NegateNode>(variableNode);
            }
            else{
                //if it is positive we can just get the variable
                nodeToPush = table.GetVariable(word);
            }
            stack.push(nodeToPush);
        }
        //if it is a function call
        else if(is_function_call(word)){
            throw std::logic_error("Procedure calls are not yet fully implemented\n");
            //HandleProcedureCall(table, word);
        }
        //otherwise, we have an operator
        else{
            std::shared_ptr<TreeNode> value1 = stack.top();
            stack.pop();

            std::shared_ptr<TreeNode> value2 = nullptr;
            //check if we have a second value
            if(!stack.empty()){
                value2 = stack.top();
                stack.pop();
            }


            if(word == "+"){
                std::shared_ptr<TreeNode> addNode(new AddNode(value2, value1));
                stack.push(addNode);
            }
            else if(word == "-"){
                std::shared_ptr<TreeNode> minusNode(new SubtractNode(value2, value1));
                stack.push(minusNode);
            }
            else if(word == "*"){
                std::shared_ptr<TreeNode> multiplyNode(new MultiplyNode(value2, value1));
                stack.push(multiplyNode);
            }
            else if(word == "/"){
                std::shared_ptr<TreeNode> divideNode(new DivideNode(value2, value1));
                stack.push(divideNode);
            }
            else if(word == "^"){
                std::shared_ptr<TreeNode> exponentNode(new ExponentNode(value2, value1));
                stack.push(exponentNode);
            }
            //else if it is a function call
        }
    }
    //return the result of the evaluation
    return stack.top();
}

/// Takes the parsed words and translates them into a collection of tokens that the LL1 parser understands
/// \param words the words you wish to translate to an understandable format
/// \param dataTypes the data types that could occur in words
/// \return An expression object with all the tokens and all the words for the expression
Expression TranslateWordsToTokens(std::vector<std::string> words, const std::vector<std::string>& dataTypes) {
    //used to loop through the vector of strings
    std::vector<std::string>::iterator str;
    //will hold all the strings we translated to int tokens
    std::vector<int> tokens;
    //hold all the text of the expression
    std::vector<std::string> text;

    for(str = words.begin(); str != words.end(); str++){
        std::string word = *str;
        //check what type of token this is

        if(is_positive_number(word)){
            tokens.push_back(NUM_TOKEN);
            text.push_back(word);
        }
        else if(is_data_type(word, dataTypes)){
            tokens.push_back(DATA_TYPE_TOKEN);
            text.push_back(word);
        }
        else if(word == "procedure") {
            tokens.push_back(PROCEDURE_TOKEN);
            text.push_back(word);
        }
        else if(word == "return") {
            tokens.push_back(RETURN_TOKEN);
            text.push_back(word);
        }
        else if(is_positive_name(word)){
            tokens.push_back(NAME_TOKEN);
            text.push_back(word);
        }
        //if the first char is a space check if everything else is a num
        else if(word.at(0) == ' ' && is_Neg_Num(word.substr(1, word.size()))){
            //if the last token is a value token we have a subtraction operation
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NUM_TOKEN);
                text.emplace_back("-");
                text.push_back(word.substr(2, word.size()));
            }
            //otherwise, we have a negative num
            else{
                tokens.push_back(SPACE_NEG_NUM_TOKEN);
                text.push_back(word.substr(1, word.size()));
            }
        }
        //if the first char is a space check if everything else is a name
        else if(word.at(0) == ' ' && is_Neg_Name(word.substr(1, word.size()))){
            //if the last token is a value token we have a subtraction operation
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NAME_TOKEN);
                text.emplace_back("-");
                text.push_back(word.substr(2, word.size()));
            }
            //otherwise, we have a negative num
            else{
                tokens.push_back(SPACE_NEG_NAME_TOKEN);
                text.push_back(word.substr(1, word.size()));
            }
        }
            //if the first char is a negative check if everything else is a num
        else if(word.at(0) == '-' && is_positive_number(word.substr(1, word.size()))){
            //if the last token is a value token we have a subtraction operation
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NUM_TOKEN);
                text.emplace_back("-");
                text.push_back(word.substr(1, word.size()));
            }
            //otherwise, we have a negative num
            else{
                tokens.push_back(NEG_NUM_TOKEN);
                text.push_back(word);
            }
        }
            //if the first char is a negative check if everything else is a name
        else if(word.at(0) == '-' && is_positive_name(word.substr(1, word.size()))){
            if(!tokens.empty() && is_Value_Token(tokens.back())){
                tokens.push_back(MINUS_TOKEN);
                tokens.push_back(NAME_TOKEN);
                text.emplace_back("-");
                text.push_back(word.substr(1, word.size()));
            }
            else{
                tokens.push_back(NEG_NAME_TOKEN);
                text.push_back(word);
            }
        }
        else if(word == "+"){
            tokens.push_back(PLUS_TOKEN);
            text.push_back(word);
        }
        else if(word == "-" || word == " -"){
            tokens.push_back(MINUS_TOKEN);
            text.emplace_back("-");
        }
        else if(word == "*"){
            tokens.push_back(MULTIPLY_TOKEN);
            text.push_back(word);
        }
        else if(word == "/"){
            tokens.push_back(DIVIDE_TOKEN);
            text.push_back(word);
        }
        else if(word == "^"){
            tokens.push_back(POWER_TOKEN);
            text.push_back(word);
        }
        else if(word == "="){
            tokens.push_back(EQUALS_TOKEN);
            text.push_back(word);
        } 
        else if(word == "("){
            tokens.push_back(OPEN_PAREN_TOKEN);
            text.push_back(word);
        }
        else if(word == ")"){
            tokens.push_back(CLOSE_PAREN_TOKEN);
            text.push_back(word);
        }
        else if(word == "{"){
            tokens.push_back(OPEN_CURLY_TOKEN);
            text.push_back(word);
        }
        else if(word == "}"){
            tokens.push_back(CLOSE_CURLY_TOKEN);
            text.push_back(word);
        }
        else if(word == ","){
            tokens.push_back(COMMA_TOKEN);
            text.push_back(word);
        }
            //if we could not find a match than push an error token
        else{
            tokens.push_back(ERROR_TOKEN);
            break;
        }
    }

    //push the end of file to the end of the vector
    tokens.push_back(END_TOKEN);

    return {tokens, text};
}

void Expression::EvaluateExpression(Table& table) {

    bool startsWithDataType = tokens.front() == DATA_TYPE_TOKEN;
    bool isProcedureDeclaration = tokens[1] == PROCEDURE_TOKEN;
    //if we start with a datatype and are not declaring a procedure
    if(startsWithDataType && !isProcedureDeclaration){
        DeclareNewVariable(table);
    }
    //look for an equals sign
    auto it = std::find(tokens.begin(), tokens.end(), EQUALS_TOKEN);
    //if we have an equals sign we are performing an assignment operation
    if( it != tokens.end()){
        int indexOfEqualsSign = (int)(it - tokens.begin());
        PerformAssignmentOperation(table, indexOfEqualsSign);
    }
    //if we have an open bracket
    else if(std::find(tokens.begin(), tokens.end(), OPEN_CURLY_TOKEN) != tokens.end()){
        //add a new variable scope
        table.AddVariableScope();
        //if we are starting a new procedure
        if(isProcedureDeclaration){
            DeclareNewProcedure(table);
        }
    }
    //if the line is a return statement
    else if(tokens.front() == RETURN_TOKEN){
        //get words after the equals sign. This is our infix expression
        std::vector<std::string> infix(words.begin() + 1, words.end());
        //convert infix to postfix
        std::vector<std::string> postfix  = convertInfixToPostFix(infix);
        //give the last procedure a return operation
        table.procedures.back().AssignValue(evaluatePostFix(postfix, table));
    }
    //if we have an open bracket
    else if(std::find(tokens.begin(), tokens.end(), CLOSE_CURLY_TOKEN) != tokens.end()){
        //remove the old scope
        table.RemoveVariableScope();
    }

}

void Expression::PerformAssignmentOperation(Table& table, int indexOfEquals) {
    std::string variableName;
    std::shared_ptr<VariableNode> variable;

    //the variable name is one before the equals
    variableName = words[indexOfEquals - 1];
    //look up the variable name
    variable = table.GetVariable(variableName);
    //get words after the equals sign. This is our infix expression
    std::vector<std::string> infix(words.begin() + (indexOfEquals + 1), words.end());
    //convert infix to postfix
    std::vector<std::string> postfix  = convertInfixToPostFix(infix);
    //evaluate the expression in postfix form
    std::shared_ptr<TreeNode> valueOfVariable = evaluatePostFix(postfix, table);
    //assign the evaluated value to the variable
    variable->AssignValue(valueOfVariable);
}

void Expression::DeclareNewVariable(Table& table) {
    std::string variableName;
    //variable type is the first word
    std::string variableType = words[0];
    //the variable name is the second word
    variableName = words[1];
    //create the unassigned variable
    std::shared_ptr<VariableNode> variable(new VariableNode(nullptr, variableName, variableType));

    if(!table.AddVariable(variable)){
        throw std::logic_error(variableName + " is being declared multiple times\n");
    }
}

std::vector<std::shared_ptr<VariableNode>> Expression::DeclareNewParams(Table &table) {

    std::vector<std::shared_ptr<VariableNode>> parameters;
    //find where the parameters start
    auto it = std::find(tokens.begin(), tokens.end(), OPEN_PAREN_TOKEN);
    int indexOfOpenParen = (int)(it - tokens.begin());
    //loop through all the params. The params start after
    for(int i = indexOfOpenParen + 1; i < words.size(); i++){
        //if we hit the close parenthesis stop adding parameters
        if(tokens[i] == CLOSE_PAREN_TOKEN){
            break;
        }
        //otherwise, add a parameter
        else{
            std::string variableType = words[i]; //get the datatype
            i++;//move onto the variable name
            std::string variableName = words[i]; //get the datatype
            std::shared_ptr<VariableNode> procedureParameter(new VariableNode(nullptr, variableName, variableType));
            //add the parameter to the current scope
            table.AddVariable(procedureParameter);
            //add the parameter to the list of parameters
            parameters.push_back(procedureParameter);
            //if we have a comma next, skip it
            if(tokens[i+1] == COMMA_TOKEN){
                i++;
            }
        }
    }

    return parameters;
}

void Expression::DeclareNewProcedure(Table &table) {
    //get the return type
    std::string returnType = words[0];
    //get the procedure name
    std::string procedureName = words[2];
    //get the parameters
    std::vector<std::shared_ptr<VariableNode>> procedureParams = DeclareNewParams(table);
    ProcedureNode newProcedure = ProcedureNode(procedureName, returnType, procedureParams);
    //if we cannot add a new procedure throw an error
    if(!table.AddProcedure(newProcedure)){
        throw std::logic_error(procedureName + " is being declared multiple times without proper overloading\n");
    }

}

void Expression::HandleProcedureCall(Table &table, std::string procedureCall) {
    //get the opening and closing parenthesis
    int indexOfOpenParen = (int)procedureCall.find('(');
    int indexOfCloseParen = (int)procedureCall.find(')');

    std::string nameOfFunction = procedureCall.substr(0, indexOfOpenParen); //name of the function being called
    std::vector<std::shared_ptr<TreeNode>> functionArguments; //args being entered into the function
    std::string currentArgument;
    //get all the variables
    for(int i = indexOfOpenParen + 1; i < indexOfCloseParen; i++){
        if(procedureCall[i] == ','){
            //look up the parameter

            //check if we have a variable name
            if(is_positive_name(currentArgument)){
                //get the variable
                std::shared_ptr<VariableNode> argument = table.GetVariable(currentArgument);
                //add the argument
                functionArguments.push_back(argument);
            }
            // if it is a constant
            else if(is_number(currentArgument)){
                std::shared_ptr<TreeNode> constant;
                if(is_number(procedureCall)){
                    constant = std::make_shared<IntegerNode>(std::stoi(procedureCall));
                }
                else if(is_decimal_number(procedureCall)){
                    constant = std::make_shared<DecimalNode>(std::stod(procedureCall));
                }

                functionArguments.push_back(constant);
            }

            //reset the current argument string
            currentArgument = "";
        }
        //otherwise, add to the currentArg
        else{
            currentArgument += procedureCall[i];
        }
    }
}
