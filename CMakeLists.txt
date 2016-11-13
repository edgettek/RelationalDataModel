cmake_minimum_required(VERSION 3.5)
project(RelationalDataModel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    database.c attributes.h)

add_executable(RelationalDataModel ${SOURCE_FILES})