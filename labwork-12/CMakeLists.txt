cmake_minimum_required(VERSION 3.12)

project(
        labwork-12-SunLYous
        VERSION 1.0
)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)
