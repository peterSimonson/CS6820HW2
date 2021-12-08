project(${TARGET_NAME})
set(Sources Nodes.cpp Nodes.h Parse.cpp Parse.h Table.cpp Table.h Expression.cpp Expression.h String_Checker.cpp
        String_Checker.h Tokens.h)

add_library(${LL1_Lib_Name} ${Sources})
