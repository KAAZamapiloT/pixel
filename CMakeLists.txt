cmake_minimum_required(VERSION 3.10)
project(pixel_ppm VERSION 1.0 LANGUAGES CXX)

# ------------------ C++ setup ------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for Zed / clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------ SDL3 setup ------------------
# Path to extracted SDL3 VC binaries
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/external/SDL3-3.4.0")

# Tell CMake where SDL3Config.cmake lives
set(SDL3_DIR "${SDL3_ROOT}/cmake")

# Find SDL3 properly (this is CRITICAL on Windows)
find_package(SDL3 REQUIRED)

# ------------------ Target ------------------
add_executable(pixel_ppm
    main.cpp
)

# Your own headers
target_include_directories(pixel_ppm PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${SDL3_ROOT}/include"
)

# Link SDL3 correctly (pulls required Win32 system libs)
target_link_libraries(pixel_ppm PUBLIC
    SDL3::SDL3
)

# ------------------ Runtime DLL copy (Windows) ------------------
# SDL3 ships DLLs inside lib/<arch>
add_custom_command(TARGET pixel_ppm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL3_ROOT}/lib/x64/SDL3.dll"
    $<TARGET_FILE_DIR:pixel_ppm>
)
