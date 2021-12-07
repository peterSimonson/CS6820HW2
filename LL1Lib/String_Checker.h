//
// Created by Peter Simonson on 12/5/21.
//

#pragma once

#include <string>
#include <vector>

namespace str_check {
    bool is_number(const std::string& s);
    bool is_positive_number(const std::string& s);
    bool is_decimal_number(const std::string& number);
    bool is_Neg_Num(const std::string& s);
    bool is_name(const std::string& s);
    bool is_positive_name(const std::string& s);
    bool is_Neg_Name(const std::string& s);
    bool is_data_type(const std::string& word, const std::vector<std::string>& dataTypes);
    bool is_procedure_call(const std::string& word);
    bool is_string(const std::string& word);
}
