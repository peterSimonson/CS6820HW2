//
// Created by Peter Simonson on 10/17/21.
//

#include "Parse.h"

/// Parse the words from a line of code. Separate words based on whitespace and reserved chars such as ';'
/// Note: strings will be parsed into one word
/// \param line line of code you wish to parse the words from
/// \return vector containing the words from a line of code
std::vector<std::string> parseWords(std::string const& line){

    std::vector<std::string> words; //holds all the words from an input line
    std::string word; //holds a word we are parsing
    //whitespace chars that separate words
    const std::string whitespace = " \n\r\t\f\v";
    //these reserved chars also separate words
    const std::string keyChar = "=+-()*^/";

    for (char x : line){
        //check if x is a whitespace char. if it is then push the word
        if (whitespace.find(x) != std::string::npos){
            if(!word.empty()){
                words.push_back(word);
            }
            word = "";
        }
        //if we have a key char then we must push the word and the char
        else if(keyChar.find(x) != std::string::npos){
            if(!word.empty()){
                words.push_back(word);
            }
            //the next word we need to push is the keyChar
            word = x;
            words.push_back(word);
            word = "";
        }
        else{
            word += x;
        }
    }
    //our strings are not whitespace terminated, so we need to add the last word
    if(!word.empty()){
        words.push_back(word);
    }

    return words;
}

Parser::Parser(const std::string& line) {
    //get the input strings
    std::vector<std::string> inputWords = parseWords(line);
    //translate the input from strings into tokens
    inputTokens = TranslateWordsToTokens(inputWords);

    //initialize the stack with EOF and Goal
    stack.push_back(END_TOKEN);
    stack.push_back(START_TOKEN);

    int focus = stack.back();
    int word = inputTokens.back();
    //implements the pseudo-code in figure 3.11
//    while(true){
//        if(focus == END_TOKEN && word == END_TOKEN){
//            return;
//        }
//        if(is_terminal(focus) || focus == END_TOKEN){
//
//        }
//    }
}

/// This function implements figure 3.4 from the text book.
/// It will swap whatever is on the back of the stack with the whatever the table wants
/// \param rule the swap from figure 3.4 you will perform
void Parser::SwapStack(int rule) {
    //replace item in back of vector
    stack.pop_back();

    switch (rule) {
        case 0:
            stack.push_back(EXPR_TOKEN);
            break;
        case 1:
            stack.push_back(EXPR_PRIME_TOKEN);
            stack.push_back(TERM_TOKEN);
            break;
        case 2:
            stack.push_back(EXPR_PRIME_TOKEN);
            stack.push_back(TERM_TOKEN);
            stack.push_back(PLUS_TOKEN);
            break;
        case 3:
            stack.push_back(EXPR_PRIME_TOKEN);
            stack.push_back(TERM_TOKEN);
            stack.push_back(MINUS_TOKEN);
            break;
        //epsilon cases. do nothing
        case 4:
        case 8:
            break;
        case 5:
            stack.push_back(TERM_PRIME_TOKEN);
            stack.push_back(FACTOR_TOKEN);
            break;
        case 6:
            stack.push_back(TERM_PRIME_TOKEN);
            stack.push_back(FACTOR_TOKEN);
            stack.push_back(MULTIPLY_TOKEN);
            break;
        case 7:
            stack.push_back(TERM_PRIME_TOKEN);
            stack.push_back(FACTOR_TOKEN);
            stack.push_back(DIVIDE_TOKEN);
            break;
        case 9:
            stack.push_back(CLOSE_PARAN_TOKEN);
            stack.push_back(EXPR_TOKEN);
            stack.push_back(OPEN_PARAN_TOKEN);
            break;
        case 10:
            stack.push_back(NUM_TOKEN);
            break;
        case 11:
            stack.push_back(NAME_TOKEN);
            break;
        //if we did not get a valid number than we have an error
        default:
            stack.push_back(ERROR_TOKEN);
    }
}
