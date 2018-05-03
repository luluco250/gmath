cmake_minimum_required(VERSION 3.11.0)
project(gmath)

include_directories(include)

file(GLOB SOURCES "source/*.cpp")

add_library(gmath SHARED ${SOURCES})
