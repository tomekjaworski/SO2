cmake_minimum_required(VERSION 3.17)
project(nibble_stream C)

set(CMAKE_C_STANDARD 11)
add_compile_options(
        "-pedantic"
        "-Werror"
        "-Wall"
        "-Wextra"
        "-fmax-errors=5"
        "-Werror=vla"
        "-Wno-error=unused-parameter"
        "-Wno-error=implicit-fallthrough"
        "-Wno-error=parentheses"
        "-Wno-parentheses"
        "-D_GNU_SOURCE"
        "-D_TEST_BOOTSTRAP"
        "-DINSIDE_DANTE")

add_executable(nibble_stream main.c)
target_link_libraries(nibble_stream m pthread)


