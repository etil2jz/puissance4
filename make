#!/bin/bash
clang-15 -O3 -m64 main.c
x86_64-w64-mingw32-gcc -g -o jeu_win main.c
