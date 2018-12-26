cmake_minimum_required(VERSION 3.13)
project(linedecoder)

set(CMAKE_CXX_STANDARD 11)

add_executable(linedecoder main.cpp clhlib_linedecoder.c clhlib_linedecoder.h clhlib_ringbuffer.c clhlib_ringbuffer.h tty.cpp tty.h)



