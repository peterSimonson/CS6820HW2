//
// Created by Peter Simonson on 12/5/21.
//
#include "gtest/gtest.h"
#include "../../LL1Lib/String_Checker.h"

namespace {
    TEST(TableTests, IsNumTest){
        std::string test = "123";
        ASSERT_TRUE(str_check::is_positive_number(test));

        test = "12.3";
        ASSERT_TRUE(str_check::is_positive_number(test));

        test = ".3";
        ASSERT_FALSE(str_check::is_positive_number(test));

        test = "test";
        ASSERT_FALSE(str_check::is_positive_number(test));

        test = ".test";
        ASSERT_FALSE(str_check::is_positive_number(test));

        test = "1.2.3";
        ASSERT_FALSE(str_check::is_positive_number(test));

        test = ".";
        ASSERT_FALSE(str_check::is_positive_number(test));
    }

    TEST(TableTests, IsNameTest){
        std::string test = "123";
        ASSERT_FALSE(str_check::is_positive_name(test));

        test = "test";
        ASSERT_TRUE(str_check::is_positive_name(test));

        test = "test123";
        ASSERT_TRUE(str_check::is_positive_name(test));

        test = "test_123";
        ASSERT_TRUE(str_check::is_positive_name(test));

        test = "test___________123";
        ASSERT_TRUE(str_check::is_positive_name(test));

        test = "test___________123";
        ASSERT_TRUE(str_check::is_positive_name(test));

        test = "123test";
        ASSERT_FALSE(str_check::is_positive_name(test));

        test = "123_test";
        ASSERT_FALSE(str_check::is_positive_name(test));

        test = "test!";
        ASSERT_FALSE(str_check::is_positive_name(test));
    }

    TEST(TableTests, IsFucntionCallTest){

        std::string test = "peter";
        ASSERT_FALSE(str_check::is_procedure_call(test));

        test = "peter(";
        ASSERT_FALSE(str_check::is_procedure_call(test));
        test = "peter)";
        ASSERT_FALSE(str_check::is_procedure_call(test));
        test = "(peter)";
        ASSERT_FALSE(str_check::is_procedure_call(test));
        test = "1peter()";
        ASSERT_FALSE(str_check::is_procedure_call(test));

        test = "peter()";
        ASSERT_TRUE(str_check::is_procedure_call(test));

    }
}
