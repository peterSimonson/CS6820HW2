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

    table.CleanUpTable();

    return CORRECT_NUM_OF_ARGS;
}

void RunTestFiles(){
    std::cout << "Reading expressions from: Test/TestResources/HW3Test.txt" <<std::endl << std::endl;

    std::ifstream file("../Test/TestResources/irassignment.txt");//holds file we are opening
    std::string line; //holds a single expression we wish to parse

    if(!file.is_open()){
        std::cout << "Could not open file containing HW3Test";
        return;
    }

    //generate our table
    Table table = Table();

    //read each line from the file
    while (std::getline(file, line)){

        Parser parse = Parser(line, table);
        if(parse.successfulParse){
            //try to evaluate the line
            try{
                parse.EvaluateLine(table);
            }
            //normally we would just kill the program if we cannot evaluate but in this instance
            //we want to keep going and test the entire file
            catch(const std::exception &exc) {
                std::cout << "Error evaluating:\t" << line <<std::endl;
                std::cout << exc.what();
            }
        }
        //stop because we failed to parse a line
        else{
            return;
        }
    }

    file.close();
    std::vector<std::shared_ptr<VariableNode>> currentScope = table.variableScopes.back();
    for(auto it = currentScope.begin(); it != currentScope.end(); it++){

        std::string output = "Current Value of: " + it->get()->variableType + " " + it->get()->variableName + " = ";
        try{
            if(it->get()->variableType == "num"){
                //so we are saving all values as doubles and converting them back to ints at the very end if need be
                output += std::to_string((int)it->get()->EvaluateNode());
            }
            else{
                output += std::to_string(it->get()->EvaluateNode());
            }
        }
        catch(...){
            output += "UNASSIGNED";
        }

        std::cout << output << std::endl;
    }

    //table.CleanUpTable();
}
