cmake_minimum_required(VERSION 3.10)

# 1. Project Name and Version
project(pixel_ppm VERSION 1.0)

# 2. Specify the C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Include Directories
# This tells CMake where to look for your .h files (the "Promises")
include_directories(include)

# 4. Collect Source Files
# We include Main.cpp from the root and everything in the src folder
set(SOURCES
    Main.cpp
    src/storage.cpp
    src/Renderer.cpp
)

# 5. Create the Executable
# This builds the "Guts" into a runnable file
add_executable(${pixel_ppm} ${SOURCES})
