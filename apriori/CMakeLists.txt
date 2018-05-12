cmake_minimum_required(VERSION 3.10)
project(apriori)

set(CMAKE_CXX_STANDARD 11)

add_library(apriori SHARED FileLoader.h get_one_itemset.h get_one_itemset.cpp FileLoader.cpp)
set_target_properties(apriori PROPERTIES LINKER_LANGUAGE CXX)