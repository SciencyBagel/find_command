# CMakeList.txt : CMake project for find_command, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("find_command")

# Add source to this project's executable.
add_executable (find_command "src/find_command.cpp" "include/find_command.h" "include/utilities.h"  "src/utilities.cpp")

# TODO: Add tests and install targets if needed.
