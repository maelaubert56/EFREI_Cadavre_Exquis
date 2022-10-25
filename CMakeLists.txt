cmake_minimum_required(VERSION 3.22)
project(PROJET_L2_SDD2_GEN_PHRASES C)

set(CMAKE_C_STANDARD 11)

add_executable(PROJET_L2_SDD2_GEN_PHRASES
        main.c dico_10_lignes.txt node.c node.h chartree.c chartree.h displaytree.c displaytree.h)
