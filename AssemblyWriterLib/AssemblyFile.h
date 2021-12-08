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
    //signifies the start of the program
    std::string entryPoint;
    //data and code sections
    section dataSection;
    section bssSection;
    section textSection;
    //will hold the file name we are going to create
    std::string fileName;
    std::string stringFormatter;
    std::string numFormatter;
    std::string ishFormatter;

    AssemblyFile();

    void WriteAssemblyFile();
    void AddInitializedString(std::string name, std::string text);
    void AddUnInitializedNum(std::string name);
    void AddInitializedNum(std::string name, int value);
    void AddInitializedIsh(std::string name, double value);
    void SetNumToConstant(std::string name, int value);
    void SetTempRegister(std::string source, bool isVariable);
    void SetVariableToTempRegister(std::string destination);
    void AddOrSubVariable(std::string source, bool isSourceAVariable, std::string operation);
    void MulOrDivVariable(std::string source, bool isSourceAVariable, std::string operation);
    void ExponentVariable(std::string power, bool isVariable);
    void WriteStringPrint(std::string dataToPrint, bool isVariable);
    void WriteNumPrint(std::string dataToPrint, bool isVariable);
    void WriteIshPrint(std::string dataToPrint);

};

void writeSectionToFile(section sectionToWrite, std::ofstream& file);

#endif //C820COMPILER_ASSEMBLYFILE_H
