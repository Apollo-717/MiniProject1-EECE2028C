cmake_minimum_required(VERSION 3.31)
project(MiniProject1_EECE2028C)

set(CMAKE_CXX_STANDARD 20)

add_executable(MiniProject1_EECE2028C src/main.cpp
        src/DoubleyLinkedList.cpp
        include/DoubleyLinkedList.h
        src/Student.cpp
        include/Student.h
        include/Node.h
)
