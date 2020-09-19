cmake_minimum_required(VERSION 3.17)
project(Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game main.cpp Headers/Spaceship.cpp Headers/Spaceship.h)
target_link_libraries(Game sfml-system sfml-window sfml-graphics sfml-audio)