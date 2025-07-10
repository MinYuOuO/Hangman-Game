cmake_minimum_required(VERSION 3.10)
project(Hangman VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("D:/Program Files/SFML-3.0.0/include/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window Audio) # SFML 3

add_executable(Hangman
    src/main.cpp
    src/modulars.cpp
)

target_link_libraries(Hangman
    SFML::Graphics 
    SFML::Window
    SFML::Audio 
)
