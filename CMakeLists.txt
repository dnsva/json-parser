
cmake_minimum_required(VERSION 3.10)

project(json-parser VERSION 0.1 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(json-parser # for now even tho this is very wrong
	include/lexer.cpp
)