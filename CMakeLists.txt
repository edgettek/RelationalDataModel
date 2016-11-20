cmake_minimum_required(VERSION 3.5)
project(RelationalDataModel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        csg.c attributes.h snap.c cp.c cdh.c cr.c part2.c part3.c main.c)

add_executable(RelationalDataModel ${SOURCE_FILES})