cmake_minimum_required(VERSION 3.10)
project(VDSProject CXX C)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 ${LLVM_CXX_FLAGS} ")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")

option(ENABLE_ADDRESS_SANITIZER "Enable AddressSanitizer for memory leak detection" OFF)
If(ENABLE_ADDRESS_SANITIZER)

    set(ASAN_FLAGS "-fsanitize=address")

    add_compile_options(${ASAN_FLAGS})

    add_link_options(${ASAN_FLAGS})
endif()

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${CMAKE_SOURCE_DIR}/gtest/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/gtest/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/gtest/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_SOURCE_DIR}/gtest/googletest-src
        ${CMAKE_SOURCE_DIR}/gtest/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

#Include dirs
include_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/src/test/)
link_directories(${CMAKE_SOURCE_DIR}/src/test/)

include_directories(${CMAKE_SOURCE_DIR}/src/bench/)
link_directories(${CMAKE_SOURCE_DIR}/src/bench/)

include_directories(${CMAKE_SOURCE_DIR}/src/verify/)
link_directories(${CMAKE_SOURCE_DIR}/src/verify/)

#target_link_libraries(VDSProject Manager)
#target_link_libraries(VDSProject gtest gtest_main pthread)

add_subdirectory(src)
add_executable(VDSProject src/main.cpp)
#target_link_libraries(VDSProject Manager)
# Verlinke die gtest- und gtest_main-Bibliotheken
target_link_libraries(VDSProject
        Manager
        gtest
        gtest_main
)