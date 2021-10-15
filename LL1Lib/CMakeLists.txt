project({TARGET_NAME})

add_library(${PARSER_LIB_NAME}
        trim.cpp trim.h
        ProgramScanner.cpp ProgramScanner.h
        AssemblyFile.cpp AssemblyFile.h)
