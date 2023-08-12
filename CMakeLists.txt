cmake_minimum_required(VERSION 3.26)
project(Wordle_Player)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Wordle_Player
        Trie.cpp
        Trie.h
        main.cpp
        WordlePlayer.cpp
        WordlePlayer.h
        WordleSimulator.cpp
        WordleSimulator.h)
