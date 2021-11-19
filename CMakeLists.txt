cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME CS6820HW2 CACHE INTERNAL "")      # program name
set(LL1_Lib_Name LL1Lib CACHE INTERNAL "") # set the name of the parser library

enable_testing()

project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(${TARGET_NAME} main.cpp)

add_subdirectory(${LL1_Lib_Name}) #Contains our library
add_subdirectory(Test)

#linke the libraries
target_link_libraries(${TARGET_NAME} ${LL1_Lib_Name})
target_link_directories(${TARGET_NAME} PRIVATE ${LL1_Lib_Name})
