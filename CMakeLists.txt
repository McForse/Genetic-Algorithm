cmake_minimum_required(VERSION 3.15)
project(Genetic-Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(GA Main.cpp GeneticAlgorithm.cpp Chromosome.h)