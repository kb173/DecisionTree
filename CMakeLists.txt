cmake_minimum_required(VERSION 3.14)
project(DecisionTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(DecisionTree main.cpp CSVReader.cpp CSVReader.h FrequencyTable.cpp FrequencyTable.h EntropyCalculator.cpp EntropyCalculator.h DecisionTree.cpp DecisionTree.h)