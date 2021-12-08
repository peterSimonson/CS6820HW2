#include <iostream>
#include <fstream>
#include "LL1Lib/Parse.h"
#include "stdexcept"

#define NUM_OF_COMMAND_LINE_ARGS 2
#define INCORRECT_NUM_OF_ARGS_ERR 1
#define CORRECT_NUM_OF_ARGS 0

void RunTestFiles();
void ConvertFileToAssembly(const std::string& fileName);

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
        std::cout << "Usage: ./CS6820 <File>" << std::endl;
        std::cout << "\t<File>: String containing the file you wish to convert to assembly." << std::endl;
        exit(INCORRECT_NUM_OF_ARGS_ERR);
    }

    //grab the file name the user entered
    std::string fileName = argv[1];

    ConvertFileToAssembly(fileName);

    return CORRECT_NUM_OF_ARGS;
}

void ConvertFileToAssembly(const std::string& fileName){
    std::cout << "Converting " << fileName << " to x86 assembly code" <<std::endl;

    std::ifstream file(fileName);//holds file we are opening
    std::string line; //holds a single expression we wish to parse

    if(!file.is_open()){
        std::cout << "Could not open file " << fileName;
        return;
    }

    //generate our table
    Table table = Table();

    //read each line from the file
    while (std::getline(file, line)){
        //parse each line
        Parser parse = Parser(line, table);
        //if we successfully parsed a line, evaluate the line
        if(parse.successfulParse){
            parse.EvaluateLine(table);
        }
        //otherwise, we did not parse successfully and need to print an error message
        else{
            throw std::logic_error("Error Parsing " + line);
        }
    }
}

void RunTestFiles(){
    std::cout << "Reading expressions from: Test/TestResources/HW3Test.txt" <<std::endl << std::endl;

    std::ifstream file("../Test/TestResources/HW3Test.txt");//holds file we are opening
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
    for(auto & variable : currentScope){

        std::string output = "Current Value of: " + variable->type + " " + variable->name + " = ";
        try{
            if(variable->type == "num"){
                //so we are saving all values as doubles and converting them back to ints at the very end if need be
                output += std::to_string((int)variable->EvaluateNode());
            }
            else{
                output += std::to_string(variable->EvaluateNode());
            }
        }
        catch(...){
            output += "UNASSIGNED";
        }

        std::cout << output << std::endl;
    }
}
