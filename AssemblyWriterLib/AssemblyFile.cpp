//
// Created by Peter Simonson on 10/2/21.
//

#include <fstream>
#include "AssemblyFile.h"
#include <stdexcept>

///Used to init default values in every assembly file.
AssemblyFile::AssemblyFile() {
    //initialize section names
    dataSection.sectionName = ".data";
    bssSection.sectionName = ".bss";
    textSection.sectionName = ".text";
    //initialize the entry point
    entryPoint = "_main";

    //save names of format strings
    stringOutFormatter = "formatOutStr";
    numOutFormatter = "formatOutInt";
    ishOutFormatter = "formatOutIsh";
    numInFormatter = "formatInNum";

    //add format strings to data section
    AddInitializedString(stringOutFormatter, "\"%s\", 10");
    AddInitializedString(numOutFormatter, "\"%d\", 10");
    AddInitializedString(ishOutFormatter, "\"%f\", 10");
    AddInitializedString(numInFormatter, "\"%d\"");

    //these are our parameters we will use for function calls
    assemblyParameters = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};

    //write the beginning of the asm file
    std::string line = entryPoint + ":";
    textSection.sectionLines.push_back(line);
    textSection.sectionLines.emplace_back("push rbx");
}

///Once you have populated an assembly file object, run this class to create the .asm file
void AssemblyFile::WriteAssemblyFile() {

    std::ofstream fileHandle(fileName);//holds file we are writing to

    //write the global entry point
    fileHandle << "global " << entryPoint << "\n";
    //write extern statement for
    fileHandle << "extern _printf" << "\n";
    fileHandle << "extern _scanf" << "\n";
    fileHandle << "\n";

    //write the exit call
    textSection.sectionLines.emplace_back("pop rbx");
    textSection.sectionLines.emplace_back("ret");

    //add the procedures to the end of text
    textSection.sectionLines.insert(textSection.sectionLines.end(), procedureLines.begin(), procedureLines.end());

    //write each section to the file
    writeSectionToFile(dataSection, fileHandle);
    writeSectionToFile(bssSection, fileHandle);
    writeSectionToFile(textSection, fileHandle);


    fileHandle.close(); //all done writing
}

/// This method takes a section and it writes it to the file
/// \param sectionToWrite the section you wish to write
/// \param file the file you wish to write the section to
void writeSectionToFile(section sectionToWrite, std::ofstream& file){

    //only write section if we have lines to write
    if(!sectionToWrite.sectionLines.empty()){
        file << "section " << sectionToWrite.sectionName << "\n";

        //loop through the lines
        std::vector<std::string>::iterator line;
        for(line = sectionToWrite.sectionLines.begin(); line != sectionToWrite.sectionLines.end(); line++){
            file << "\t" <<*line << "\n";
        }
        //write some whitespace
        file << "\n";
    }

}

/// Adds an initialized string variable to the .data section
/// \param name the name of the variable you wish to create
/// \param text the text you wish to be contained in the in the variable
void AssemblyFile::AddInitializedString(const std::string& name, const std::string& text){

    dataSection.sectionLines.push_back(name + ":");
    dataSection.sectionLines.emplace_back("default rel");
    std::string dataLine = "  db  " + text + ", 0";
    dataSection.sectionLines.push_back(dataLine);

}

/// Adds an initialized num variable to the .data section
/// \param name name of the variable
/// \param value value you wish to be saved in the num
void AssemblyFile::AddInitializedNum(const std::string& name, int value){
    dataSection.sectionLines.push_back(name + ":" + " dq " + std::to_string(value));
}

void AssemblyFile::AddInitializedIsh(const std::string& name, double value) {
    dataSection.sectionLines.push_back(name + ":" + " dq " + std::to_string(value));
}

/// adds an uninitialized variable to the .bss section
/// \param name the name of the variable
void AssemblyFile::AddUnInitializedNum(const std::string& name){
    bssSection.sectionLines.push_back(name + ": resb 8");
}

/// Sets the value of a previously defined variable to a constant
/// \param name name of the variable you wish to set
/// \param value integer value you wish to set to the constant
void AssemblyFile::SetNumToConstant(const std::string& name, int value){
    //push rax because we are going to use it
    textSection.sectionLines.emplace_back("push rax");
    //move the value into rax and then into the variable
    textSection.sectionLines.push_back("mov rax," + std::to_string(value));
    textSection.sectionLines.push_back("mov [" + name + "], rax");
    //pop rax back because we are done with it
    textSection.sectionLines.emplace_back("pop rax");
}

/// Sets the value of the temporary register rcx to either a variable or a constant
/// \param source the value you wish to set rax to
/// \param isVariable is rax a variable or not
void AssemblyFile::SetRegister(const std::string &source, bool isVariable, const std::string &registerToSet,
                               bool isProcedure) {

    std::vector<std::string> * sectionToWrite;
    if(isProcedure){
        sectionToWrite = &procedureLines;
    }
    else{
        sectionToWrite = & textSection.sectionLines;
    }

    //move source into rcx.
    if(isVariable){
        sectionToWrite->push_back("mov " + registerToSet + ", [" + source + "]");
    }
    else{
        sectionToWrite->push_back("mov " + registerToSet + "," + source);
    }

}

/// Take the value you have in the temp register rax and put it into a variable
/// \param destinationVariable the variable which will store the value from temp register rcx
void AssemblyFile::SetVariableToRegister(const std::string& destinationVariable, const std::string& registerSource) {

    textSection.sectionLines.push_back("mov [" + destinationVariable + "], " + registerSource);
}

void AssemblyFile::AddOrSub(const std::string &destination, const std::string &operation, const std::string &rhs,
                            bool isProcedure) {

    std::vector<std::string> * sectionToWrite;
    if(isProcedure){
        sectionToWrite = &procedureLines;
    }
    else{
        sectionToWrite = & textSection.sectionLines;
    }

    //add rax to the destination
    sectionToWrite->push_back(operation +" "+ destination +", " + rhs);

}

void AssemblyFile::MulOrDivVariable(const std::string &destination, const std::string &operation, std::string &rhs,
                                    bool isProcedure) {

    std::vector<std::string> * sectionToWrite;
    if(isProcedure){
        sectionToWrite = &procedureLines;
    }
    else{
        sectionToWrite = & textSection.sectionLines;
    }

    //the rhs register cannot be rax because that is the left-hand side
    if(rhs == "rbx"){
        //set the value of rax into rbx
        sectionToWrite->emplace_back("mov rbx, " + rhs);
        //change the rhs register to rbx
        rhs = "rbx";
    }

    //move the destination value into rax
    sectionToWrite->emplace_back("mov rax, " + destination);
    //perform the operation on rax and rbx. result is saved in rax
    sectionToWrite->push_back(operation + " " + rhs);
    //store rax in the variable
    sectionToWrite->emplace_back("mov "+ destination + ", rax");

}

void AssemblyFile::ExponentVariable(const std::string &power, const std::string &baseRegister, bool isProcedure) {

    std::vector<std::string> * sectionToWrite;
    if(isProcedure){
        sectionToWrite = &procedureLines;
    }
    else{
        sectionToWrite = & textSection.sectionLines;
    }

    sectionToWrite->emplace_back("push rax");
    sectionToWrite->emplace_back("push rbx");
    sectionToWrite->emplace_back("push rdi");

    //move the base value into rax
    sectionToWrite->emplace_back("mov rax, " + baseRegister);
    //move the multiply value into rbx
    sectionToWrite->emplace_back("mov rbx, " + baseRegister);
    //move the counter into rdi
    sectionToWrite->emplace_back("mov rdi, 1");


    //save the labels which should have unique names
    std::string againLabel = "again" + std::to_string(dataSection.sectionLines.size());
    std::string doneLabel = "done" + std::to_string(dataSection.sectionLines.size());

    //label for the beginning of our loop
    sectionToWrite->push_back(againLabel + ":");
    //see if we are done looping
    sectionToWrite->emplace_back("cmp rdi, " + power);
    sectionToWrite->push_back("jge " + doneLabel);
    //if we are not done looping multiply rax by the default value
    sectionToWrite->emplace_back("mul rbx");
    //increase the counter
    sectionToWrite->emplace_back("inc rdi");
    //repeat the loop
    sectionToWrite->push_back("jmp " + againLabel);
    //save the label for where to go once the loop is finished
    sectionToWrite->push_back(doneLabel + ":");

    //move the final value back into rcx
    sectionToWrite->emplace_back("mov " + baseRegister + ", rax");

    sectionToWrite->emplace_back("pop rdi");
    sectionToWrite->emplace_back("pop rbx");
    sectionToWrite->emplace_back("pop rax");
}

/// Write a printf call for a num. Supports constants and variables
/// \param dataToPrint the data you wish to print. Either a num variable or a string containing a num
/// \param isVariable is dataToPrint a constant or a variable
void AssemblyFile::WriteNumPrint(const std::string& dataToPrint, bool isVariable){

    textSection.sectionLines.push_back("lea rdi, [" + numOutFormatter + "]");
    //if it is a variable put the variable into rsi
    if(isVariable){
        textSection.sectionLines.push_back("mov rsi, [" + dataToPrint + "]");
    }
    //if it is not a variable than put a constant into rsi
    else{
        textSection.sectionLines.push_back("mov rsi, " + dataToPrint);
    }

    textSection.sectionLines.emplace_back("xor rax, rax");
    textSection.sectionLines.emplace_back("call _printf");
}

/// Prints a string. Can support printing a variable or a constant
/// \param dataToPrint the data you wish to print. Either a variable name or a constant string
/// \param isVariable is dataToPrint either a variable or a constant
void AssemblyFile::WriteStringPrint(const std::string& dataToPrint, bool isVariable){
    textSection.sectionLines.push_back("lea rdi, [" + stringOutFormatter + "]");
    std::string nameOfVariableToPrint;
    //if it is a variable save the name of the variable
    if(isVariable){
        nameOfVariableToPrint = dataToPrint;
    }
    //else it is a string constant. We need to create a new string and save the variable name
    else{
        nameOfVariableToPrint = "writeConstant" + std::to_string(dataSection.sectionLines.size());
        AddInitializedString(nameOfVariableToPrint, dataToPrint);
    }

    textSection.sectionLines.push_back("lea rsi, [" + nameOfVariableToPrint + "]");
    textSection.sectionLines.emplace_back("xor rax, rax");
    textSection.sectionLines.emplace_back("call _printf");

}

/// Print an ish. Only accepts variables
/// \param dataToPrint the name of the ish variable you wish to print
void AssemblyFile::WriteIshPrint(const std::string& dataToPrint) {
    //offset to 16 bit addressing
    textSection.sectionLines.emplace_back("sub rsp, 8");
    //add the printf formatter
    textSection.sectionLines.push_back("lea rdi, [" + ishOutFormatter + "]");
    //add the variable move
    textSection.sectionLines.push_back("movq xmm0, qword [" + dataToPrint + "]");
    //set rax to 1
    textSection.sectionLines.emplace_back("mov rax, 1");
    //call printf
    textSection.sectionLines.emplace_back("call _printf");
    //reset offset
    textSection.sectionLines.emplace_back("add rsp, 8");
}

/// Write a assembly scanf call for a num
/// \param readDestination the destination where you wish to store the scanf results
void AssemblyFile::WriteNumRead(const std::string& readDestination) {
    //add the scanf formatter
    textSection.sectionLines.push_back("lea rdi, [" + numInFormatter + "]");
    //add the destination for scanf data
    textSection.sectionLines.push_back("lea rsi, [" + readDestination + "]");
    //zero out rax
    textSection.sectionLines.emplace_back("xor rax, rax");
    //call scanf
    textSection.sectionLines.emplace_back("call _scanf");
}

void AssemblyFile::WriteProcedurePrologue(const std::string &procedureName) {
    //add the name of the procedure
    procedureLines.push_back(procedureName + ":");
    procedureLines.emplace_back("push rbp");
    procedureLines.emplace_back("mov rbp, rsp");
}

void AssemblyFile::WriteProcedureEpilogue() {
    procedureLines.emplace_back("mov rsp, rbp");
    procedureLines.emplace_back("pop rbp");
    procedureLines.emplace_back("ret");
}

