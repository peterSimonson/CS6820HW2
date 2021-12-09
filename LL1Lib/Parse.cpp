//
// Created by Peter Simonson on 10/17/21.
//

#include <iostream>
#include "Parse.h"
#include "stdexcept"

void PrintParserError(const std::string& expr);

/// Parse the words from a line of code. Separate words based on whitespace and reserved chars such as ';'
/// Note: strings will be parsed into one word
/// \param line line of code you wish to parse the words from
/// \return vector containing the words from a line of code
std::vector<std::string> parseWords(std::string const& line){

    std::vector<std::string> words; //holds all the words from an input line

    //whitespace chars that separate words
    const std::string whitespace = " \n\r\t\f\v";
    //these reserved chars also separate words
    const std::string keyChar = "=+-()*^/,{}";
    const char doubleQuote = '\"';
    bool inString = false;

    auto it = line.begin();
    std::string word; //holds a word we are parsing

    //put while loop here to get all words
    bool leadingWhiteSpace = false;
    while(it != line.end()){
        //check if there is whitespace leading up to our term
        while(whitespace.find(*it) != std::string::npos && !inString){
            if(!word.empty()){
                words.push_back(word);
                word = "";
            }
            leadingWhiteSpace = true;
            it++;
        }

        //if the first non-whitespace char is a minus, and we have leading whitespace we have a spacenegnum
        if(*it == '-' && !inString){
            if(!word.empty()){
                words.push_back(word);
                word = "";
            }

            if(leadingWhiteSpace){
                word += " "; //add the leading whitespace
                leadingWhiteSpace = false;
            }
            word += *it; //add the minus sign
            it++; //increment the iterator
            while(whitespace.find(*it) != std::string::npos){
                leadingWhiteSpace = true;
                it++;
            }
        }
        //if we found a quote
        else if(*it == doubleQuote){
            word += *it;
            //if we were already in a string we have an end-quote
            if(inString){
                words.push_back(word);
                word = "";
                inString = false;
            }
            //otherwise, we are beginning a quote
            else{
                inString = true;
            }
            it++;
        }
        else if(keyChar.find(*it) != std::string::npos && !inString){
            if(!word.empty()){
                words.push_back(word);
            }
            //the next word we need to push is the keyChar
            word = *it;
            words.push_back(word);
            word = "";
            it ++;
            leadingWhiteSpace = false;
        }
        else{
            word += *it;
            it++;
        }
    }
    //our strings are not whitespace terminated, so we need to add the last word
    if(!word.empty()){
        words.push_back(word);
    }
    //check that we do not have a string without an end
    if(inString){
        throw std::range_error("Line is missing an end quote " + line);
    }

    return words;
}

/// Parse a expression. Will check for validity and store result in successfulParse
/// \param line the expression you wish to parse for validity
/// \param table the table containing information about our language
Parser::Parser(const std::string& line, Table& table) {
    //get the input strings
    std::vector<std::string> inputWords = parseWords(line);
    //translate the input from strings into tokens
    expr = TranslateWordsToTokens(inputWords, table.dataTypes);

    std::vector<int> LL1Stack;

    //initialize the stack with EOF and Goal
    LL1Stack.push_back(END_TOKEN);
    LL1Stack.push_back(START_TOKEN);

    //declare reverse iterators to traverse our stack and input
    int focus = LL1Stack.back();
    auto word = expr.tokens.begin();
    //implements the pseudo-code in figure 3.11
    successfulParse = false;
    while(true){
        //if both the focus and the word are EOF then we have successfully completed a parse
        if(focus == END_TOKEN && *word == END_TOKEN){
            LL1Stack.pop_back(); //remove end token
            successfulParse = true;
            return;
        }
        //check if focus is terminal
        if(is_terminal(focus)){
            //if the word matches the focus
            if(focus == *word){
                //go to next word
                word++;
                //go to next word on stack and pop the last
                LL1Stack.pop_back();
                focus = LL1Stack.back();
            }
            else{
                //print an error message
                PrintParserError(line);
                return;
            }
        }
        //if word or focus is an error
        else if(focus == ERROR_TOKEN || *word == ERROR_TOKEN){
            //print error message
            PrintParserError(line);
            return;
        }
        //otherwise, focus is non-terminal, and we need to swap it out
        else{
            //look up the swap rule we must perform
            int rule = table.LookUpTable(*word, focus);
            if(rule == ERROR_TOKEN){
                //print error message
                PrintParserError(line);
                return;
            }
            //perform the swap
            SwapStack(rule, LL1Stack, table);
            focus = LL1Stack.back(); //move focus to the back of the stack
        }
    }
}

/// This function implements figure 3.4 from the text book.
/// It will swap whatever is on the back of the stack with the whatever the table wants
/// \param ruleIndex the swap from figure 3.4 you will perform
void Parser::SwapStack(int ruleIndex, std::vector<int> & stack, Table table) {
    //get the SwapRule at the index
    rule SwapRule = table.rules[ruleIndex];
    //back of stack must match lhs
    if(stack.back() == SwapRule.leftHandSide){
        //replace item in back of vector
        stack.pop_back();

        //push the items back in reverse using reverse iteration
        for(auto it = SwapRule.rightHandSide.rbegin(); it != SwapRule.rightHandSide.rend(); it++){
            if(*it != EPSILON_TOKEN){
                stack.push_back(*it);
            }
        }
    }
    //else print an error
    else{

    }

}

void Parser::EvaluateLine(Table &table, AssemblyFile &file) {
    //Evaluate the line you just parsed
    expr.EvaluateExpression(table, file);
}

/// Print an error message when you fail to parse an expression
/// \param expr the expression you failed to parse
void PrintParserError(const std::string& expr){
    std::cout << "Error Parsing:\t" << expr << std::endl;
}
