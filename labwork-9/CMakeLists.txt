cmake_minimum_required(VERSION 3.23)
project(labwork_9_SunLYous)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(labwork_9_SunLYous main.cpp Allocator.h PoolClass.h PoolClass.cpp)
