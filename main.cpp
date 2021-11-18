#include <iostream>
#include <fstream>
#include "LL1Lib/Parse.h"

#define NUM_OF_COMMAND_LINE_ARGS 2
#define INCORRECT_NUM_OF_ARGS_ERR 1
#define CORRECT_NUM_OF_ARGS 0

void RunTestFiles();

int main(int argc, char *argv[]) {
    std::cout << "CS6820 LL(1) Parser" << std::endl;

    //if no command line args are entered just run the test files
    if(argc == 1){
        RunTestFiles();
        return CORRECT_NUM_OF_ARGS;
    }
    //check command line args
    else if(argc != NUM_OF_COMMAND_LINE_ARGS){
        std::cout << "Error: Incorrect number of arguments entered." << std::endl;
        std::cout << "Usage: ./CS6820 <Expr>" << std::endl;
        std::cout << "\t<Expr>: String containing the mathematical expression you wish to parse." << std::endl;
        exit(INCORRECT_NUM_OF_ARGS_ERR);
    }

    //grab the expression the user entered
    std::string expression = argv[1];

    //holds our table
    Table table;

    //initialize a parser with the expression the user entered
    Parser parser = Parser(expression, table);

    return CORRECT_NUM_OF_ARGS;
}

void RunTestFiles(){
    std::cout << "Part 1: Parse Invalid Expressions" <<std::endl << std::endl;

    std::ifstream file("../Test/TestResources/BadExpressions.txt");//holds file we are opening
    std::string line; //holds a single expression we wish to parse
    bool encounteredAnError = false;

    if(!file.is_open()){
        std::cout << "Could not open file containing good expressions";
        return;
    }

    //generate our table
    Table table = Table();

    //read each line from the file
    while (std::getline(file, line)){
        Parser parse = Parser(line, table);
        if(parse.successfulParse){
            encounteredAnError = true;
        }
    }

    file.close();

    std::cout << std::endl << "Part 2: Parse Valid Expressions" <<std::endl << std::endl;

    file.open("../Test/TestResources/GoodExpressions.txt");

    if(!file.is_open()){
        std::cout << "Could not open file containing bad expressions";
        return;
    }

    //read each line from the file
    while (std::getline(file, line)){
        Parser parse = Parser(line, table);
        if(!parse.successfulParse){
            encounteredAnError = true;
        }
    }

    file.close();

    if(encounteredAnError){
        std::cout << std::endl <<"Not all expressions were successfully parsed" << std::endl;
    }
    else{
        std::cout << std::endl <<"All expressions were successfully parsed" << std::endl;
    }
}
