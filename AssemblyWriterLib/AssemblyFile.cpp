//
// Created by Peter Simonson on 10/2/21.
//

#include <fstream>
#include "AssemblyFile.h"

///Used to init default values in every assembly file.
AssemblyFile::AssemblyFile() {
    //initialize section names
    dataSection.sectionName = ".data";
    bssSection.sectionName = ".bss";
    textSection.sectionName = ".text";
    //initialize the entry point
    entryPoint = "_main";

    //save names of format strings
    stringFormatter = "formatStr";
    numFormatter = "formatInt";
    ishFormatter = "formatIsh";

    //add format strings to data section
    AddInitializedString(stringFormatter, "\"%s\", 10");
    AddInitializedString(numFormatter, "\"%d\", 10");
    AddInitializedString(ishFormatter, "\"%f\", 10");
}

///Once you have populated an assembly file object, run this class to create the .asm file
void AssemblyFile::WriteAssemblyFile(){

    std::ofstream fileHandle(fileName);//holds file we are writing to

    //write the global entry point
    fileHandle << "global " << entryPoint << "\n";
    //write extern statement for
    fileHandle << "extern _printf" << "\n";
    fileHandle << "\n";

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
void AssemblyFile::AddInitializedString(std::string name, std::string text){

    dataSection.sectionLines.push_back(name + ":");
    dataSection.sectionLines.emplace_back("default rel");
    std::string dataLine = "  db  " + text + ", 0";
    dataSection.sectionLines.push_back(dataLine);

}

/// Adds an initialized num variable to the .data section
/// \param name name of the variable
/// \param value value you wish to be saved in the num
void AssemblyFile::AddInitializedNum(std::string name, int value){
    dataSection.sectionLines.push_back(name + ":" + " dq " + std::to_string(value));
}

void AssemblyFile::AddInitializedIsh(std::string name, double value) {
    dataSection.sectionLines.push_back(name + ":" + " dq " + std::to_string(value));
}

/// adds an uninitialized variable to the .bss section
/// \param name the name of the variable
void AssemblyFile::AddUnInitializedNum(std::string name){
    bssSection.sectionLines.push_back(name + ": resb 8");
}

/// Sets the value of a previously defined variable to a constant
/// \param name name of the variable you wish to set
/// \param value integer value you wish to set to the constant
void AssemblyFile::SetNumToConstant(std::string name, int value){
    //push rax because we are going to use it
    textSection.sectionLines.emplace_back("push rax");
    //move the value into rax and then into the variable
    textSection.sectionLines.push_back("mov rax," + std::to_string(value));
    textSection.sectionLines.push_back("mov [" + name + "], rax");
    //pop rax back because we are done with it
    textSection.sectionLines.emplace_back("pop rax");
}

void AssemblyFile::SetTempRegister(std::string source, bool isVariable) {
    //push rax and rcx because we are going to use them
    textSection.sectionLines.emplace_back("push rcx");

    //move source into rcx.
    if(isVariable){
        textSection.sectionLines.push_back("mov rcx, [" + source + "]");
    }
    else{
        textSection.sectionLines.push_back("mov rcx, " + source);
    }

}

void AssemblyFile::SetVariableToTempRegister(std::string destination){

    textSection.sectionLines.push_back("mov [" + destination + "], rcx");
    //now that we have loaded rcx into the destination we can pop it back
    textSection.sectionLines.emplace_back("pop rcx");
}

void AssemblyFile::AddOrSubVariable(std::string source, bool isSourceAVariable, std::string operation) {
    //push rax because we are going to use it
    textSection.sectionLines.emplace_back("push rax");

    //if the source is a variable move its value into rax
    if(isSourceAVariable){
        textSection.sectionLines.push_back("mov rax, [" + source + "]");
    }
    //otherwise, move the constant into rax
    else{
        textSection.sectionLines.push_back("mov rax, " + source);
    }

    //add rax to the destination
    textSection.sectionLines.emplace_back(operation +" rcx, " + "rax");

    //pop rax back because we are done with it
    textSection.sectionLines.emplace_back("pop rax");
}

void AssemblyFile::MulOrDivVariable(std::string source, bool isSourceAVariable, std::string operation) {
    //push rax and bbx because we are going to use them
    textSection.sectionLines.emplace_back("push rax");
    textSection.sectionLines.emplace_back("push rbx");

    //if the source is a variable move its value into rbx
    if(isSourceAVariable){
        textSection.sectionLines.push_back("mov rbx, [" + source + "]");
    }
    //otherwise, move the constant into rbx
    else{
        textSection.sectionLines.push_back("mov rbx, " + source);
    }

    //move the destination value into rax
    textSection.sectionLines.emplace_back("mov rax, rcx");
    //perform the operation on rax and rbx. result is saved in rax
    textSection.sectionLines.push_back(operation  + " rbx");
    //store rax in the variable
    textSection.sectionLines.emplace_back("mov rcx, rax");

    //pop rax and rbx back because we are done with those registers
    textSection.sectionLines.emplace_back("pop rbx");
    textSection.sectionLines.emplace_back("pop rax");
}

void AssemblyFile::ExponentVariable(std::string power, bool isVariable) {
    textSection.sectionLines.emplace_back("push rax");
    textSection.sectionLines.emplace_back("push rbx");
    textSection.sectionLines.emplace_back("push rdi");
    textSection.sectionLines.emplace_back("push rsi");

    //move the base value into rax
    textSection.sectionLines.emplace_back("mov rax, rcx");
    //move the multiply value into rbx
    textSection.sectionLines.emplace_back("mov rbx, rax");
    //move the counter into rdi
    textSection.sectionLines.emplace_back("mov rdi, 1");

    //move the count limit into rsi
    if(isVariable){
        textSection.sectionLines.push_back("mov rsi, [" + power + "]");
    }
    else{
        textSection.sectionLines.push_back("mov rsi, " + power);
    }

    //save the labels which should have unique names
    std::string againLabel = "again" + std::to_string(dataSection.sectionLines.size());
    std::string doneLabel = "done" + std::to_string(dataSection.sectionLines.size());

    //label for the beginning of our loop
    textSection.sectionLines.push_back(againLabel + ":");
    //see if we are done looping
    textSection.sectionLines.emplace_back("cmp rdi, rsi");
    textSection.sectionLines.push_back("jge " + doneLabel);
    //if we are not done looping multiply rax by the default value
    textSection.sectionLines.emplace_back("mul rbx");
    //increase the counter
    textSection.sectionLines.emplace_back("inc rdi");
    //repeat the loop
    textSection.sectionLines.push_back("jmp " + againLabel);
    //save the label for where to go once the loop is finished
    textSection.sectionLines.push_back(doneLabel + ":");

    //move the final value back into rcx
    textSection.sectionLines.emplace_back("mov rcx, rax");

    textSection.sectionLines.emplace_back("pop rsi");
    textSection.sectionLines.emplace_back("pop rdi");
    textSection.sectionLines.emplace_back("pop rbx");
    textSection.sectionLines.emplace_back("pop rax");
}

void AssemblyFile::WriteNumPrint(std::string dataToPrint, bool isVariable){

    textSection.sectionLines.push_back("lea rdi, [" + numFormatter + "]");
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

void AssemblyFile::WriteStringPrint(std::string dataToPrint, bool isVariable){
    textSection.sectionLines.push_back("lea rdi, [" + stringFormatter + "]");
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

void AssemblyFile::WriteIshPrint(std::string dataToPrint) {
    //offset to 16 bit addressing
    textSection.sectionLines.emplace_back("sub rsp, 8");
    //add the printf formatter
    textSection.sectionLines.push_back("lea rdi, [" + ishFormatter + "]");
    //add the variable move
    textSection.sectionLines.push_back("movq xmm0, qword [" + dataToPrint + "]");
    //set rax to 1
    textSection.sectionLines.emplace_back("mov rax, 1");
    //call printf
    textSection.sectionLines.emplace_back("call _printf");
    //reset offset
    textSection.sectionLines.emplace_back("add rsp, 8");
}
