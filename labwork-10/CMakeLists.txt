cmake_minimum_required(VERSION 3.25)
project(labwork_10_SunLYous)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(labwork_10_SunLYous main.cpp ViewClass.h ViewClass.cpp ControllerClass.h ControllerClass.cpp ModelClass.h ModelClass.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

target_link_libraries(labwork_10_SunLYous PRIVATE cpr::cpr)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(labwork_10_SunLYous PRIVATE nlohmann_json::nlohmann_json)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(BUILD_SHARED_LIBS OFF)
include(FetchContent)

FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui GIT_TAG v4.0.0)

FetchContent_MakeAvailable(ftxui)
target_link_libraries(labwork_10_SunLYous PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)