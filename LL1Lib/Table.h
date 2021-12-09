//
// Created by Peter Simonson on 10/18/21.
//

#ifndef CS6820HW2_TABLE_H
#define CS6820HW2_TABLE_H


#include <vector>
#include <string>
#include <map>
#include "Nodes.h"
#include "Tokens.h"


//structure for a production rule
class rule{
public:
    int leftHandSide;
    std::vector<int> rightHandSide;
};

class Table {
public:
    Table();
    void CleanUpTable();
    //holds the first set
    std::map<int, std::vector<int>> firstSet;
    //holds the follow set
    std::map<int, std::vector<int>> followSet;
    //holds the productions
    std::map<int, rule> rules;
    //holds the data types
    std::vector<std::string> dataTypes;
    //Vector of vectors that holds the variable scopes
    std::vector<std::vector<std::shared_ptr<VariableNode>>> variableScopes;
    //holds the procedures
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
    //holds the table
    int RuleTable [NUM_OF_TOKENS - NUM_OF_NON_TERMINALS][NUM_OF_NON_TERMINALS]{};

    int LookUpTable(int row, int column);
    void GenerateRules();
    void GenerateFirstSet();
    void GenerateFollowSet();
    void BuildTable();
    void addRule(int lhs, std::vector<int>&& rhs);
    std::vector<int> findFirstPlusSet(rule production);
    bool is_already_a_var(const std::string& nameOfVariable);
    std::shared_ptr<VariableNode> GetVariable(const std::string& nameOfVariableToReturn);
    std::shared_ptr<ProcedureNode> GetProcedure(const std::string& nameOfProcedureToReturn, const std::vector<std::shared_ptr<TreeNode>>& functionArguments);
    bool AddVariable(const std::shared_ptr<VariableNode>& varToAdd);
    bool AddProcedure(const ProcedureNode& procedureToAdd);
    void AddVariableScope();
    void RemoveVariableScope();
};


#endif //CS6820HW2_TABLE_H
