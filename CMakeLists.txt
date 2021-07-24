cmake_minimum_required(VERSION 3.10)
project(Master VERSION 1.0)

add_executable(Master null.c)
target_sources(Master
    PRIVATE
    "src/Decoder.c")

target_include_directories(Master
    PUBLIC
    inc)
