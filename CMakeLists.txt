cmake_minimum_required(VERSION 3.10)

project(MyGPS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(MyGPS
        src/main.cpp
        src/menu.cpp
        src/creatingMap.cpp
        Functions/independentRoutePlanning.cpp
        Functions/restrictedRoutePlanning.cpp
        Functions/routePlanningUtils.cpp
        src/batchMode.cpp
        include/BatchMode.h
)

target_include_directories(MyGPS PRIVATE
        ../include
        ../include/data_structures
)