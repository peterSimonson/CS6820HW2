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