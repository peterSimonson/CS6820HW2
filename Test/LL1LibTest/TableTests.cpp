//
// Created by Peter Simonson on 10/18/21.
//

#include "gtest/gtest.h"
#include "../../LL1Lib/Table.h"

namespace {
    TEST(TableTests, TranslateTest){
        std::vector<std::string> words{"(" ,"peter", "+", "12", ")", "*", "2"};

        std::vector<int> tokens =  TranslateWordsToTokens(words);
        std::vector<int> results{END_TERM , OPEN_PARAN, NAME_TERM, PLUS, NUM_TERM, CLOSE_PARAN, MULTIPLY, NUM_TERM};
        ASSERT_EQ(tokens, results);

        words = {"(" ,"peter", "-", "12", ")", "/", "2"};
        tokens =  TranslateWordsToTokens(words);
        results = {END_TERM , OPEN_PARAN, NAME_TERM, MINUS, NUM_TERM, CLOSE_PARAN, DIVIDE, NUM_TERM};
        ASSERT_EQ(tokens, results);
    }
}