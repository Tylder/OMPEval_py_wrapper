cmake_minimum_required(VERSION 3.4...3.18)
project(ompeval)

## EXTERNAL
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 -Wall")

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -pthread")
endif(UNIX)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
endif(WIN32)

#add_library(omp_eval STATIC
#        ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/CardRange.cpp
#        ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/CombinedRange.cpp
#        ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/EquityCalculator.cpp
#        ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/HandEvaluator.cpp
#)
#
#target_link_libraries(cmake_example omp_eval)

message("HERE HERE HERE")

## PYBIND

add_subdirectory(pybind11)

pybind11_add_module(
    ompeval
    ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/CardRange.cpp
    ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/CombinedRange.cpp
    ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/EquityCalculator.cpp
    ${CMAKE_SOURCE_DIR}/extern/OMPEval/omp/HandEvaluator.cpp
    src/main.cpp
)


# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(ompeval PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})