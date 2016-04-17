#cmake_minimum_required(VERSION 3.5)
# Define our project, could be anything
project(TrabalhoMATA52)

# Some flags for CMAKE, as we don't want the first he will remove this
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE on)

# We will tell the system that our source will be
set(SOURCE_FILES main.c)

# And this will be our executable
# Debug Executable
add_executable(dbsg ${SOURCE_FILES})
# Release Executable
add_executable(main ${SOURCE_FILES})