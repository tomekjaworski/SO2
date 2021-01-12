cmake_minimum_required(VERSION 3.17)

get_filename_component(proj_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${proj_name} C)

add_compile_options("-pedantic" "-Werror" "-Wall" "-Wextra" "-fmax-errors=5" "-Werror=vla" "-Wno-error=unused-parameter" "-Wno-error=implicit-fallthrough" "-Wno-error=parentheses" "-Wno-parentheses" "-D_GNU_SOURCE" "-D_TEST_BOOTSTRAP" "-DINSIDE_DANTE")


add_executable(${proj_name}  alarm_main.c)
target_link_libraries(${proj_name}  m)
