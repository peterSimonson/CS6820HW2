set(Sources NodesTest.cpp ParseTest.cpp TableTests.cpp ExpressionTest.cpp String_CheckerTest.cpp)

set(LL1_LIB_TEST_NAME LL1LibTest) # set the name of the parser test library

add_executable(${LL1_LIB_TEST_NAME} ${Sources})
target_link_libraries(${LL1_LIB_TEST_NAME} PUBLIC
        gtest_main
        ${LL1_Lib_Name})

enable_testing()

include(googletest)
gtest_discover_tests(${LL1_LIB_TEST_NAME})