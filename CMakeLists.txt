cmake_minimum_required(VERSION 3.27)
project(tetris)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(tetris main.cpp
        library.cpp
        library.h
        Tetramin/Tetramin.cpp
        Tetramin/Tetramin.hpp
        Tetramin/I_Piece.cpp
        Tetramin/I_Piece.hpp
        Tetramin/O_Piece.cpp
        Tetramin/O_Piece.hpp)

target_link_libraries(tetris ${CURSES_LIBRARIES})