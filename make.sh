#!/bin/bash

sudo clang-15 -O3 main.cpp `pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags SDL2_ttf`
