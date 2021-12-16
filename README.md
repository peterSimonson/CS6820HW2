# Peter Simonson CS6820 Final Homework

This is a C++ Cmake project

## Main Executable
The main executable for this program is main.cpp in the root directory of the project. I personally use CLion to build, but you can use:

``<path to cmake>/cmake --build "<path to project>/cmake-build-debug" --target CS6820HW2 -- -j 6``

In the root directory to build. You can also run the script ``buildWithCmake.sh`` to build the project.

Once you have built the project there should be an executable called ``CS6820HW2`` located in `cmake-build-debug`. This executable accepts a string containing a mathematical expression.

### Building on Morpheus
The last time you built my program you had difficulty building the unit tests. I would recommend remove line number 17 in the root CmakeLists.txt. This line contains the statement `add_subdirectory(Test) #Contains all the tests`. Removing this will stop the unit tests from being built when you build the entire project.

I also believe you changed my version of Cmake to `cmake_minimum_required(VERSION 3.16)` in the root CmakeLists.txt file. I used 3.20 because it added features for my unit tests.

### Command Syntax

To run the program enter the following

    ./CS6820HW2 [FileName]
       OPTIONAL <FileName>: The text file you wish to convert to assembly

Please note: If you run `./CS6820HW2` without any command line arguments the program will parse all the expressions in the text file located in `./Test/TestResources/assembly-1.txt`.

## Running the output ASM file

If for whatever reason you do not build and run my program, I have included the asm file featured in the video demonstration. It should be in the root project directory and is titled `assembly-1.asm`.

I assemble and link this file using the following commands:

`nasm -f macho64 assembly-1.asm && gcc -arch x86_64 -o assembly-1 assembly-1.o`

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
This folder contains my github workflow. This workflow initializes the submodules, builds the project, and runs all the unit tests when you push to master.
