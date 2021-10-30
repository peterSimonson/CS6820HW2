#include <iostream>
#include "LL1Lib/Parse.h"

#define NUM_OF_COMMAND_LINE_ARGS 2
#define INCORRECT_NUM_OF_ARGS_ERR 1

int main(int argc, char *argv[]) {
    std::cout << "CS6820 LL(1) Parser" << std::endl;

    //check command line args
    if(argc != NUM_OF_COMMAND_LINE_ARGS){
        std::cout << "Error: Incorrect number of arguments entered." << std::endl;
        std::cout << "Usage: ./CS6820 <Expr>" << std::endl;
        std::cout << "\t<Expr>: String containing the mathematical expression you wish to parse." << std::endl;
        exit(INCORRECT_NUM_OF_ARGS_ERR);
    }

    //grab the expression the user entered
    std::string expression = argv[1];

    //holds our table
    Table table = Table();

    //initialize a parser with the expression the user entered
    Parser parser = Parser(expression, table);

    return 0;
}
