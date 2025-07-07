cmake_minimum_required(VERSION 3.20)
project(InariTx VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings for robust code
add_compile_options(-Wall -Wextra)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# Link directories for static libraries
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Force static linking for libcurl
add_definitions(-DCURL_STATICLIB)

# Find system dependencies
find_package(CURL REQUIRED)
find_library(ZLIB_LIBRARY NAMES z zlib libz PATHS ${CMAKE_SOURCE_DIR}/lib)
find_library(PNG_LIBRARY NAMES png libpng PATHS ${CMAKE_SOURCE_DIR}/lib)

# Source files
set(SOURCES
    src/main.cpp
    src/blockchain/client.cpp
    src/blockchain/bitcoin_client.cpp
    src/pdf/pdf_generator.cpp
    src/qr/qr_generator.cpp
    src/i18n/translations.cpp
    src/utils/error.cpp
    src/utils/config.cpp
)

# Executable
add_executable(InariTx ${SOURCES})

# Link libraries
target_link_libraries(InariTx PRIVATE
    hpdf
    qrcodegen
    ${CURL_LIBRARIES}
    ${ZLIB_LIBRARY}
    ${PNG_LIBRARY}
    ws2_32
    wldap32
    crypt32
)

# Windows-specific libraries
if(WIN32)
    target_link_libraries(InariTx PRIVATE iphlpapi bcrypt)
endif()