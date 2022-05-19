cmake_minimum_required(VERSION 3.17)
project(Final_Boss C)

set(CMAKE_C_STANDARD 99)

add_executable(Final_Boss main.c)
target_link_libraries(Final_Boss -lOpenGL32 -lfreeGLUT)
