cmake_minimum_required(VERSION 3.17)


project(${proj_name} C)

add_compile_options("-pedantic" "-Werror" "-Wall" "-Wextra" "-fmax-errors=5" "-Werror=vla"
        "-Wno-error=unused-parameter"
        "-Wno-error=implicit-fallthrough"
        "-Wno-error=parentheses"
        "-Wno-parentheses"
        "-Wno-unused-parameter"
        "-D_GNU_SOURCE" "-D_TEST_BOOTSTRAP" "-DINSIDE_DANTE")

add_executable(${proj_name}  main.c)
target_link_libraries(${proj_name}  m)
