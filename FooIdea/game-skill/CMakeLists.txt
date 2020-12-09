cmake_minimum_required(VERSION 3.10)
project(test)
add_executable(test src/main.cpp)
target_include_directories(test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)