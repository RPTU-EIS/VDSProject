project(VDSProject_test CXX C)
cmake_minimum_required(VERSION 3.10)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(VDSProject_test main_test.cpp ../BDD_node.cpp ../BDD_node.h)
target_link_libraries(VDSProject_test Manager)
target_link_libraries(VDSProject_test gtest gtest_main pthread)
