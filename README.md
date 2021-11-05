# Peter Simonson CS6820 Homework 2

This is a C++ Cmake project

## Main Executable
The main executable for this program is main.cpp in the root directory of the project. I personally use CLion to build, but you can use:

``<path to cmake>/cmake --build "<path to project>/cmake-build-debug" --target CS6820HW2 -- -j 6``

In the root directory to build. You can also run the script ``buildWithCmake.sh`` to build the project.

Once you have built the project there should be an executable called ``CS6820HW2`` located in `cmake-build-debug`. This executable accepts a string containing a mathematical expression.

### Command Syntax

To run the program enter the following

    ./CS6820HW2 [Expr]
       OPTIONAL <Expr>: The string containing the mathematical expression you wish to parse

Please note: If you run `./CS6820HW2` without any command line arguments the program will parse all the expressions in the text files located in `./Test/TestResources`

##LL1Lib Folder

This is a library required to run the LL1 Parser. I seperated this into a library in order to allow unit testing. Additionally, I hope having this as a separate library will be helpful in HW3.

##Test Folder

A large portion of this project is in the Test folder. I will now explain each folder in the `Test` folder

If all the Cmake Projects in `Test` are built correctly you should be able to run the command `ctest` in the `cmake-build-debug` folder to run all the unit tests I wrote.

### googletest Folder
I am using Google Test as a unit testing framework. This is a submodule meaning this folder will remain empty until you run `git submodule update --init --recursive` to initialize the submodule. Please note that this command is included in the script `buildWithCmake.sh`.

Once you initialize the submodule you should not need to do anything else for Google Test.

### LL1LibTest Folder
This folder contains all the unit tests I wrote for this homework. I believe all of the tests should pass except for the tests related to constructing the First set, Follow Set, and LL1 Table. Those tests broke when I changed my productions and I never bothered to fix them.

### TestResources Folder
This folder contains any resources needed to run the tests. For this homework I needed a file to store the valid expressions and a file to store the invalid expressions.

Note: I use the files in this folder when you run the executable without any command line arguments.

## .github Folder
This folder contains my github workflow. This workflow initializes the submodules, builds the project, and runs all the unit tests.
