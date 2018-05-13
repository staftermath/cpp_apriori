include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runAprioriTests FileLoaderTest.cpp FPTreeTest.cpp)

target_link_libraries(runAprioriTests gtest gtest_main)
target_link_libraries(runAprioriTests apriori)