cmake_minimum_required(VERSION 3.10)

project(pixel_ppm VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------ SDL3 ------------------

set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/external/SDL3-3.4.0")
set(SDL3_DIR "${SDL3_ROOT}/cmake")

find_package(SDL3 REQUIRED)

# ------------------ Target ------------------

add_executable(pixel_ppm
    main.cpp
    external/tracy/tracy-0.14.1/public/TracyClient.cpp
)

# ------------------ Tracy ------------------

target_compile_definitions(pixel_ppm PRIVATE
    TRACY_ENABLE
    TRACY_VERBOSE
)

target_include_directories(pixel_ppm PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/tracy/tracy-0.14.1/public"
)

# ------------------ Libraries ------------------

target_link_libraries(pixel_ppm PRIVATE
    SDL3::SDL3
    ws2_32
    dbghelp
    secur32
)

# ------------------ SDL3 DLL ------------------

add_custom_command(TARGET pixel_ppm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        "$<TARGET_FILE_DIR:pixel_ppm>"
)