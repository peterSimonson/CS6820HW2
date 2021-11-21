project(${TARGET_NAME})

add_subdirectory(googletest)
add_subdirectory(LL1LibTest)

set(ResourceFolder TestResources)

#include the testresource files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${ResourceFolder}/BadExpressions.txt
        ${CMAKE_CURRENT_BINARY_DIR}/${ResourceFolder}/BadExpressions.txt COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${ResourceFolder}/GoodExpressions.txt
        ${CMAKE_CURRENT_BINARY_DIR}/${ResourceFolder}/GoodExpressions.txt COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${ResourceFolder}/Procedures.txt
        ${CMAKE_CURRENT_BINARY_DIR}/${ResourceFolder}/Procedures.txt COPYONLY)