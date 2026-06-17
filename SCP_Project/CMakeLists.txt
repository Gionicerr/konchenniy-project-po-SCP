cmake_minimum_required(VERSION 3.10)
project(SCP_Foundation)

# GCC 6.3.0 has some C++17 support, but we've refactored to be safe.
# We still prefer C++17 if available.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF) # Allow fallback to C++14 if needed
set(CMAKE_CXX_EXTENSIONS OFF)

# Include current directory and SCP_classes for headers
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/SCP_classes)

# Targets
add_executable(SCP_Console SCPclass.cpp)
add_executable(SCP_Console_Clear SCPClass_clear_cmd.cpp)

# Optimization flags for better performance
if(MSVC)
    target_compile_options(SCP_Console PRIVATE /W4)
    target_compile_options(SCP_Console_Clear PRIVATE /W4)
else()
    target_compile_options(SCP_Console PRIVATE -Wall -Wextra)
    target_compile_options(SCP_Console_Clear PRIVATE -Wall -Wextra)
endif()