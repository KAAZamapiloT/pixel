cmake_minimum_required(VERSION 3.10)
project(pixel_ppm VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- SDL3 root (VC binaries) ----
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/external/SDL3-3.4.0")

add_executable(pixel_ppm
    main.cpp
)

# ---- Your existing includes ----
target_include_directories(pixel_ppm PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${SDL3_ROOT}/include"
)

# ---- Link SDL3 (MSVC .lib) ----
target_link_libraries(pixel_ppm PRIVATE
    "${SDL3_ROOT}/lib/x64/SDL3.lib"
)

# ---- Copy SDL3.dll next to exe (REQUIRED ON WINDOWS) ----
add_custom_command(TARGET pixel_ppm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_ROOT}/bin/x64/SDL3.dll"
    $<TARGET_FILE_DIR:pixel_ppm>
)
