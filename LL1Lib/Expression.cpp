//
// Created by Peter Simonson on 11/11/21.
//

#include <stack>
#include <algorithm>
#include "Expression.h"
#include "Nodes.h"
#include "String_Checker.h"
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
        if(str_check::is_name(*word)){
            std::string wordToPush = *word;

            //if the next word is an open parenthesis we have a function call
            if(*(word + 1) == "("){
                //hold the number of open and close parentheses in the call
                //this is helpful if we have a function call in side of a function call
                int openCount = 1;
                int closeCount = 0;
                word++;
                wordToPush += *word;
                while (openCount != closeCount){
                    word++;
                    if(*word == ")"){
                        closeCount ++;
                    }
                    else if(*word == "("){
                        openCount++;
                    }
                    wordToPush += *word;
                }
            }
            postFixExpression.push_back(wordToPush);
        }
        //if it is a number push it back of the stack
        else if(str_check::is_number(*word)){
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
        if(str_check::is_number(word)){
            stack.push(HandleNumber(word));
        }
        //if it is a variable
        else if(str_check::is_name(word)){
            stack.push(HandleVariable(table, word));
        }
        //if it is a function call
        else if(str_check::is_procedure_call(word)){
            //get a populated procedure node
            stack.push(HandleProcedureCall(table, word));
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

        if(str_check::is_positive_number(word)){
            tokens.push_back(NUM_TOKEN);
            text.push_back(word);
        }
        else if(str_check::is_data_type(word, dataTypes)){
            tokens.push_back(DATA_TYPE_TOKEN);
            text.push_back(word);
        }
        else if(str_check::is_string(word)){
            tokens.push_back(STRING_TOKEN);
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
        else if(word == "printNum") {
            tokens.push_back(PRINT_NUM_TOKEN);
            text.push_back(word);
        }
        else if(word == "printIsh") {
            tokens.push_back(PRINT_ISH_TOKEN);
            text.push_back(word);
        }
        else if(word == "printString") {
            tokens.push_back(PRINT_STRING_TOKEN);
            text.push_back(word);
        }
        else if(str_check::is_positive_name(word)){
            tokens.push_back(NAME_TOKEN);
            text.push_back(word);
        }
        //if the first char is a space check if everything else is a num
        else if(word.at(0) == ' ' && str_check::is_Neg_Num(word.substr(1, word.size()))){
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
        else if(word.at(0) == ' ' && str_check::is_Neg_Name(word.substr(1, word.size()))){
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
        else if(word.at(0) == '-' && str_check::is_positive_number(word.substr(1, word.size()))){
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
        else if(word.at(0) == '-' && str_check::is_positive_name(word.substr(1, word.size()))){
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

void Expression::EvaluateExpression(Table &table, AssemblyFile &file) {

    bool startsWithDataType = tokens.front() == DATA_TYPE_TOKEN;
    bool isProcedureDeclaration = tokens[1] == PROCEDURE_TOKEN;
    //look for an equals sign
    auto equalsIt = std::find(tokens.begin(), tokens.end(), EQUALS_TOKEN);
    //see if we have assignment
    bool hasEquals = equalsIt != tokens.end();

    //if we start with a datatype and are not declaring a procedure
    if(startsWithDataType && !isProcedureDeclaration){
        DeclareNewVariable(table, !hasEquals, file);
    }
    //if we have an equals sign we are performing an assignment operation
    if(hasEquals){
        int indexOfEqualsSign = (int)(equalsIt - tokens.begin());
        PerformAssignmentOperation(table, indexOfEqualsSign, file);
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
        table.procedures.back()->AssignValue(evaluatePostFix(postfix, table));
    }
    //if we have a close bracket
    else if(std::find(tokens.begin(), tokens.end(), CLOSE_CURLY_TOKEN) != tokens.end()){
        //remove the old scope
        table.RemoveVariableScope();
    }
    //if the first token is a print token
    else if(is_Print_Token(tokens.front())){
        //we need to handle a print statement
        HandlePrintStatement(table, words[1], tokens.front(), file);
    }

}

void Expression::PerformAssignmentOperation(Table &table, int indexOfEquals, AssemblyFile &file) {
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
    std::shared_ptr<TreeNode> variableOperation = evaluatePostFix(postfix, table);

    //this is a sad workaround...
    //try to evaluate the expression
    try{
        //assign the evaluated value to the variable
        variable->AssignValue(HandleType(variable));
    }
    //if we are in a method we cannot evaluate yet because parameters are not assigned
    catch (std::runtime_error const & err){
        variable->AssignValue(variableOperation);
        //if the variable has not been declared in assembly, and we are in the global scope
        if(!variable->declaredInAsm && table.variableScopes.size() == 1){
            if(variable->type == "ish"){
                file.AddInitializedIsh(variableName, variable->EvaluateNode());
            }
            else if(variable->type == "num"){
                file.AddInitializedNum(variableName, (int) variable->EvaluateNode());
            }
            //we have now declared the variable
            variable->declaredInAsm = true;
        }
    }

}

void Expression::DeclareNewVariable(Table &table, bool unitializedVariable, AssemblyFile &file) {
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

    //check if we need to add an uninitialized num to the assembly file
    if(unitializedVariable){
        file.AddUnInitializedNum(variableName);
        //we have declared this in assembly
        variable->declaredInAsm = true;
    }
}

std::vector<std::shared_ptr<VariableNode>> Expression::DeclareNewParams(Table &table) {

    std::vector<std::shared_ptr<VariableNode>> parameters;
    //find where the parameters start
    auto it = std::find(tokens.begin(), tokens.end(), OPEN_PAREN_TOKEN);
    int indexOfOpenParen = (int)(it - tokens.begin());
    //loop through all the params. The params start after open paren
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

std::shared_ptr<TreeNode> HandleProcedureCall(Table &table, std::string procedureCall) {
    //get the opening and closing parenthesis
    int indexOfOpenParen = (int)procedureCall.find_first_of('(');
    int indexOfCloseParen = (int)procedureCall.find_last_of(')');

    std::string procedureName = procedureCall.substr(0, indexOfOpenParen); //name of the function being called
    std::vector<std::shared_ptr<TreeNode>> procedureArgs; //args being entered into the function
    std::string currentArgument; //the argument we are currently parsing
    //we want to keep track of the total parentheses we have encountered in case we have another function call inside
    int openCount = 1;
    int closeCount = 0;
    //get all the variables between the parentheses
    for(int i = indexOfOpenParen + 1; i <= indexOfCloseParen; i++){
        //if we are at a comma or a close paren we must add the currentArgument to the list
        if((procedureCall[i] == ',' || i == indexOfCloseParen) && openCount == closeCount + 1){

            std::shared_ptr<TreeNode> argument;
            //check if we have a procedure call
            if(str_check::is_procedure_call(currentArgument)){
                //evaluate the procedure call inside the procedure call
                argument = HandleProcedureCall(table, currentArgument);
            }
            //check if we have a variable name
            else if(str_check::is_name(currentArgument)) {
                argument = HandleVariable(table, currentArgument);
            }
            // if it is a constant
            else if(str_check::is_number(currentArgument)){
                argument = HandleNumber(currentArgument);
            }
            //add the argument
            procedureArgs.push_back(argument);

            //reset the current argument string
            currentArgument = "";
        }
        else if(procedureCall[i] == ')'){
            closeCount++;
            currentArgument += procedureCall[i];
        }
        else if(procedureCall[i] == '('){
            openCount++;
            currentArgument += procedureCall[i];
        }
        //otherwise, add to the currentArg
        else{
            currentArgument += procedureCall[i];
        }
    }

    //get the procedure being called
    std::shared_ptr<ProcedureNode> procedureToCall = table.GetProcedure(procedureName, procedureArgs);

    //populate the arguments
    for(int i = 0; i < procedureToCall->procedureParameters.size(); i++){
        //set the args to the ones we parsed
        procedureToCall->procedureParameters[i]->AssignValue(procedureArgs[i]);
    }

    //find the data type of the variable and use that type
    return HandleType(procedureToCall);
}

std::shared_ptr<TreeNode> HandleVariable(Table &table, const std::string& variable) {
    std::shared_ptr<TreeNode> nodeToReturn;
    //if it is a negative variable
    if(str_check::is_Neg_Name(variable)){
        //get the variable name without the minus sign
        std::shared_ptr<VariableNode> variableNode = table.GetVariable(variable.substr(1, variable.size()));
        //add the negative of variable node
        nodeToReturn =  std::make_shared<NegateNode>(variableNode);
    }
    else{
        //if it is positive we can just get the variable
        nodeToReturn = table.GetVariable(variable);
    }

    return nodeToReturn;
}

std::shared_ptr<TreeNode> HandleNumber(const std::string& number) {
    std::shared_ptr<TreeNode> nodeToReturn;
    //check if it is a decimal
    if(str_check::is_decimal_number(number)){
        nodeToReturn = std::make_shared<DecimalNode>(std::stod(number));
    }
        //otherwise, it must be an integer
    else{
        nodeToReturn = std::make_shared<IntegerNode>(std::stoi(number));
    }
    return nodeToReturn;
}

std::shared_ptr<TreeNode> HandleType(const std::shared_ptr<ObjectNode>& NodeToEval) {
    std::shared_ptr<TreeNode> nodeToReturn;

    //find the data type of the variable and use that type
    if(NodeToEval->type == "num"){
        nodeToReturn = std::make_shared<IntegerNode>(IntegerNode((int)NodeToEval->EvaluateNode()));
    }
    else if(NodeToEval->type == "ish"){
        nodeToReturn = std::make_shared<DecimalNode>(DecimalNode(NodeToEval->EvaluateNode()));
    }
    return nodeToReturn;
}

void HandlePrintStatement(Table &table, const std::string& valueToPrint, int printType, AssemblyFile &file) {
    //Note: for ish and nums we only print variables
    //      for strings we only print constants

    switch (printType) {
        case PRINT_STRING_TOKEN:
            file.WriteStringPrint(valueToPrint, false);
            break;
        case PRINT_NUM_TOKEN:
            table.GetVariable(valueToPrint);
            file.WriteNumPrint(valueToPrint, true);
            break;
        case PRINT_ISH_TOKEN:
            table.GetVariable(valueToPrint);
            file.WriteIshPrint(valueToPrint);
            break;
    }
}


