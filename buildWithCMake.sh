#Running this script will build the project with CMake. It will also initialize any git submodules
#Note if you do not have cmake or do not wish to use CMake there should be a MakeFile already in cmake-build-debug

git submodule update --init --recursive

cd cmake-build-debug || exit

#generate the cmake cache
cmake ..
#this will build the project
cmake --build .
