cmake_minimum_required(VERSION 3.23)
project(labwork_7_SunLYous)

include_directories(.)

add_executable(labwork_7_SunLYous
        main.cpp
        ParentFrame.cpp
        ParentFrame.h
        ParseMP3.cpp
        ParseMP3.h
        Information.cpp
        Information.h
        ParseCommand.h
        ParseCommand.cpp)
