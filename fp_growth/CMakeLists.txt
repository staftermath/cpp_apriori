cmake_minimum_required(VERSION 3.10)
project(apriori)

set(CMAKE_CXX_STANDARD 11)

add_library(apriori SHARED include/FileLoader.hpp src/FileLoader.cpp src/FPTree.cpp include/FPTree.hpp src/ARule.cpp include/ARule.hpp)
set_target_properties(apriori PROPERTIES LINKER_LANGUAGE CXX)