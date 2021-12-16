#include <iostream>
#include <fstream>
#include "LL1Lib/Parse.h"
#include "stdexcept"
#include "AssemblyWriterLib/AssemblyFile.h"

#define NUM_OF_COMMAND_LINE_ARGS 2
#define INCORRECT_NUM_OF_ARGS_ERR 1
#define CORRECT_NUM_OF_ARGS 0

void ConvertFileToAssembly(const std::string& fileName);
std::string replaceFirstOccurrence(std::string s, const std::string& toReplace, const std::string& replaceWith);
bool isEmptyOrCommentLine(std::string & line);

int main(int argc, char *argv[]) {
    std::cout << "CS6820 LL(1) Parser" << std::endl;

    //if no command line args are entered just run the test files
    if(argc == 1){
        ConvertFileToAssembly("../Test/TestResources/assembly-1.txt");
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

    std::ifstream file(fileName);//holds file we are opening
    std::string line; //holds a single expression we wish to parse

    if(!file.is_open()){
        std::cout << "Could not open file " << fileName;
        return;
    }

    std::cout << "Converting " << fileName << " to x86 assembly code" <<std::endl;

    //generate our table
    Table table = Table();
    //generate the file we will be writing
    AssemblyFile asmFile = AssemblyFile();


    //read each line from the file
    while (std::getline(file, line)){
        if(isEmptyOrCommentLine(line)){
            continue;
        }

        //parse each line
        Parser parse = Parser(line, table);
        //if we successfully parsed a line, evaluate the line
        if(parse.successfulParse){
            parse.EvaluateLine(table, asmFile);
        }
        //otherwise, we did not parse successfully and need to print an error message
        else{
            throw std::logic_error("Error Parsing " + line);
        }
    }
    //close the file
    file.close();

    //set the output file name
    asmFile.fileName = replaceFirstOccurrence(fileName, ".txt", ".asm");

    //write the output file
    asmFile.WriteAssemblyFile();
}

//taken from: https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string/5878802
std::string replaceFirstOccurrence(std::string s, const std::string& toReplace, const std::string& replaceWith){
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return s;
    return s.replace(pos, toReplace.length(), replaceWith);
}

bool isEmptyOrCommentLine(std::string & line){
    if(line.empty() || (line.size() >= 2 && line[0] == '/' && line[1] == '/')){
        return true;
    }
    else{
        return false;
    }
}