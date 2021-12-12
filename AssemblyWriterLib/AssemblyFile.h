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
    //holds the lines for procedures
    std::vector<std::string> procedureLines;
    //will hold the file name we are going to create
    std::string fileName;
    std::string stringOutFormatter;
    std::string numOutFormatter;
    std::string ishOutFormatter;
    std::string numInFormatter;

    AssemblyFile();

    void WriteAssemblyFile();
    void AddInitializedString(const std::string& name, const std::string& text);
    void AddUnInitializedNum(const std::string& name);
    void AddInitializedNum(const std::string& name, int value);
    void AddInitializedIsh(const std::string& name, double value);
    void SetNumToConstant(const std::string& name, int value);
    void SetRegister(const std::string &source, bool isVariable, const std::string &registerToSet,
                     bool isProcedure);
    void SetVariableToRegister(const std::string& destinationVariable, const std::string& registerSource);
    void AddOrSub(const std::string &destination, const std::string &operation, const std::string &rhs,
                  bool isProcedure);
    void MulOrDivVariable(const std::string &destination, const std::string &operation, std::string &rhs,
                          bool isProcedure);
    void ExponentVariable(const std::string &power, const std::string &baseRegister, bool isProcedure);
    void WriteStringPrint(const std::string& dataToPrint, bool isVariable);
    void WriteNumPrint(const std::string& dataToPrint, bool isVariable);
    void WriteIshPrint(const std::string& dataToPrint);
    void WriteNumRead(const std::string& readDestination);
    void WriteProcedurePrologue(const std::string& procedureName);
    void WriteProcedureEpilogue();

};

void writeSectionToFile(section sectionToWrite, std::ofstream& file);

#endif //C820COMPILER_ASSEMBLYFILE_H
