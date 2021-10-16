# Peter Simonson CS6820 Project 1

This is a C++ Cmake project

## Main Executable
The main executable for this program is main.cpp in the root directory of the project. I personally use Clion to build but you can use

``<path to cmake>/cmake --build "<path to project>/cmake-build-debug" --target C820Compiler -- -j 6``

In the root directory to build. You can also run the script ``buildWithCmake.sh`` to build the project.

Once you have built the project there should be an executable called ``CS6820HW2`` located in `cmake-build-debug`. This executable accepts a string containing a mathematical expression.

### Command Syntax

To run the program enter the following

    ./CS6820HW2 <Expr>
       <Expr>: The string containing the mathematical expression you wish to parse
