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
        Tetramin/O_Piece.hpp
        Tetramin/L_Piece.cpp
        Tetramin/L_Piece.hpp
        Tetramin/J_Piece.cpp
        Tetramin/J_Piece.hpp
        Tetramin/T_Piece.cpp
        Tetramin/T_Piece.hpp
        Tetramin/S_Piece.cpp
        Tetramin/S_Piece.hpp
        Tetramin/Z_Piece.cpp
        Tetramin/Z_Piece.hpp
        TetrisGame/TetrisGame.cpp
        TetrisGame/TetrisGame.hpp
        TetrisGame/GameScreen.cpp
        TetrisGame/GameScreen.hpp
        TetrisGame/MenuScreen.cpp
        TetrisGame/MenuScreen.hpp
        TetrisGame/ScoreScreen.cpp
        TetrisGame/ScoreScreen.hpp
        TetrisGame/NicknameScreen.cpp
        TetrisGame/NicknameScreen.hpp
)

target_link_libraries(tetris ${CURSES_LIBRARIES})