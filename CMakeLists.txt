cmake_minimum_required(VERSION 3.21)
project(proj5_arrayheap)

set(CMAKE_CXX_STANDARD 14)

add_executable(proj5_arrayheap driver-proj5.cpp arrayheap-prof-proj5.h
        arrayheap-student-proj5.h process-proj5.h)
