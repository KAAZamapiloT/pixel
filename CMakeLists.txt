cmake_minimum_required(VERSION 3.10)
project(pixel_ppm VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(pixel_ppm main.cpp)


target_include_directories(pixel_ppm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
