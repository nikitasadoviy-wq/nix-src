cmake_minimum_required(VERSION 3.20)

project(nix-src
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

add_executable(nix-src
    src/main.cpp
    src/cpu.cpp
    src/hash.cpp
    src/fetch.cpp
    src/build.cpp
    src/build_system.cpp
)

target_include_directories(nix-src
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(nix-src
    PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
        CURL::libcurl
)