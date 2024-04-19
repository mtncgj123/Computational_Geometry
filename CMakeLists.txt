cmake_minimum_required(VERSION 3.0)
project(Computational_Geometic)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(${CMAKE_SOURCE_DIR}
include)


add_executable(Main src/main.cpp)
# add_executable(test_2 src/test_2.cpp)
# or add_executable(my_cmake memo_system_management.cpp src/showManu.cpp src/addPerson.cpp)

set(CMAKE_CXX_STANDARD 11)