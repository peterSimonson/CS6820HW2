//
// Created by Peter Simonson on 12/5/21.
//

#include "String_Checker.h"

bool str_check::is_procedure_call(const std::string &word) {

    int indexOfOpenParen = (int)word.find('(');
    int indexOfCloseParen = (int)word.find(')');

    //if we don't have both the open and close parenthesis return false
    if(indexOfOpenParen == std::string::npos || indexOfCloseParen == std::string::npos){
        return false;
    }

    std::string nameOfFunction = word.substr(0, indexOfOpenParen);

    //if there is not a valid name
    if(!is_positive_name(nameOfFunction)){
        return false;
    }

    return true;
}

bool str_check::is_number(const std::string &s) {
    return is_positive_number(s) || is_Neg_Num(s);
}

bool str_check::is_name(const std::string &s) {
    return is_positive_name(s) || is_Neg_Name(s);
}

/// Checks if a string is a number
/// note: does not accept negative numbers
/// \param s string we want to check if it is a number
/// \return true if it is a number, false if it is not
bool str_check::is_positive_number(const std::string& s)
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
/// Note: the string must have returned true from is_positive_number
/// \param number string containing a number
/// \return true if the number is a decimal number. false if it is an integer
bool str_check::is_decimal_number(const std::string& number){
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
bool str_check::is_positive_name(const std::string& s)
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

bool str_check::is_Neg_Num(const std::string& s){
    if(s.at(0) == '-' && is_positive_number(s.substr(1, s.size()))){
        return true;
    }
    else{
        return false;
    }
}

bool str_check::is_Neg_Name(const std::string& s){
    if(s.at(0) == '-' && is_positive_name(s.substr(1, s.size()))){
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
bool str_check::is_data_type(const std::string& word, const std::vector<std::string>& dataTypes){

    if(std::find(dataTypes.begin(), dataTypes.end(), word) != dataTypes.end()){
        //if we find a match return true
        return true;
    }
    else{
        //otherwise, return false
        return false;
    }
}

bool str_check::is_string(const std::string &word) {
    const char doubleQuote = '\"';
    //if the first and last chars are double quotes return true
    if(word[0] == doubleQuote && word[word.size()-1] == doubleQuote){
        return true;
    }
    //otherwise, this is not a valid string
    else{
        return false;
    }
}
