cmake_minimum_required(VERSION 3.16)
project(Hangman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories("D:/Program Files/SFML-3.0.0/include")
set(SFML_DIR "D:/Program Files/SFML-3.0.0/lib/cmake/SFML") # SFML path

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio Network) # SFML 3

add_definitions(-DSFML_STATIC)

add_executable(hangman
    src/main.cpp
    src/modulars.cpp
    src/function.h
)

target_link_libraries(hangman PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    SFML::Network

    opengl32
    winm
)
