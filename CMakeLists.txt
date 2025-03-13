cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(MyProject
        src/main.cpp
        src/menu.cpp
        src/creatingMap.cpp
        Functions/independentRoutePlanning.cpp
        Functions/restrictedRoutePlanning.cpp
        Functions/routePlanningUtils.cpp
)

target_include_directories(MyProject PRIVATE
        ../include
        ../include/data_structures
)