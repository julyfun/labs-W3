cmake_minimum_required(VERSION 3.12)
project(get-prime)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_STANDARD 11)

include_directories("include")

add_library(lib "src/lib.c")
add_executable(w3 "src/getPrime.c")

target_link_libraries(w3 lib)
