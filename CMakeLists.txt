# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(InariTx VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the executable
add_executable(InariTx 
    src/main.cpp
    src/blockchain/client.cpp
    src/blockchain/bitcoin_client.cpp
)

# Include directories for third-party libraries
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/libharu)
include_directories(${CMAKE_SOURCE_DIR}/include/nlohmann)
include_directories(${CMAKE_SOURCE_DIR}/include/curl)

# Link static libraries
find_library(LIBHARU_LIBRARY NAMES libhpdf hpdf PATHS ${CMAKE_SOURCE_DIR}/lib)
find_library(LIBCURL_LIBRARY NAMES libcurl curl PATHS ${CMAKE_SOURCE_DIR}/lib)

# Link the libraries to the executable
target_link_libraries(InariTx PRIVATE ${LIBHARU_LIBRARY} ${LIBCURL_LIBRARY})

# Add MSYS2-specific flags for Windows
if (WIN32)
    target_link_libraries(InariTx PRIVATE ws2_32 stdc++fs) # Add stdc++fs for filesystem
endif()

# Set output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)