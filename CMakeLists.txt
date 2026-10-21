cmake_minimum_required(VERSION 3.20)
project(MiniProject1_EECE2028C LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MiniProject1_EECE2028C src/main.cpp src/DoubleyLinkedList.cpp src/Student.cpp)
include(CTest)
if(BUILD_TESTING)
    add_executable(list_tests tests/list_tests.cpp src/Student.cpp)
    add_test(NAME list_tests COMMAND list_tests)
endif()
