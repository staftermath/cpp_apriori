cmake_minimum_required(VERSION 3.10)
project(cpp_apriori)

set(CMAKE_CXX_STANDARD 11)


include_directories(fp_growth)

add_subdirectory(fp_growth)
add_subdirectory(fp_growth_tests)

add_executable(cpp_apriori main.cpp)