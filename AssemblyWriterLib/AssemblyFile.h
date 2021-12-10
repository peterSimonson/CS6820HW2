//
// Created by Peter Simonson on 10/2/21.
//

#ifndef C820COMPILER_ASSEMBLYFILE_H
#define C820COMPILER_ASSEMBLYFILE_H

#include <string>
#include <vector>

class section{
public:
    //holds the name of the section
    std::string sectionName;
    //holds the line of the section
    std::vector<std::string> sectionLines;
};

class AssemblyFile{
public:
    //these are the registers we shall use for functions
    std::vector<std::string> assemblyParameters;

    //signifies the start of the program
    std::string entryPoint;
    //data and code sections
    section dataSection;
    section bssSection;
    section textSection;
    //will hold the file name we are going to create
    std::string fileName;
    std::string stringOutFormatter;
    std::string numOutFormatter;
    std::string ishOutFormatter;
    std::string numInFormatter;

    AssemblyFile();

    void WriteAssemblyFile() const;
    void AddInitializedString(const std::string& name, const std::string& text);
    void AddUnInitializedNum(const std::string& name);
    void AddInitializedNum(const std::string& name, int value);
    void AddInitializedIsh(const std::string& name, double value);
    void SetNumToConstant(std::string name, int value);
    void SetTempRegister(std::string source, bool isVariable);
    void SetVariableToTempRegister(std::string destination);
    void AddOrSubVariable(std::string source, bool isSourceAVariable, std::string operation);
    void MulOrDivVariable(std::string source, bool isSourceAVariable, std::string operation);
    void ExponentVariable(std::string power, bool isVariable);
    void WriteStringPrint(const std::string& dataToPrint, bool isVariable);
    void WriteNumPrint(const std::string& dataToPrint, bool isVariable);
    void WriteIshPrint(const std::string& dataToPrint);
    void WriteNumRead(const std::string& readDestination);

};

void writeSectionToFile(section sectionToWrite, std::ofstream& file);

#endif //C820COMPILER_ASSEMBLYFILE_H
