cmake_minimum_required(VERSION 3.10)
project(cpp_apriori)

set(CMAKE_CXX_STANDARD 11)


include_directories(apriori)

add_subdirectory(apriori)
add_subdirectory(apriori_tests)

add_executable(cpp_apriori main.cpp)