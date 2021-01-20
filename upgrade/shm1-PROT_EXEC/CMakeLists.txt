cmake_minimum_required(VERSION 3.17)

get_filename_component(proj_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${proj_name} C)
set(LINKER_SCRIPT "linker.lds")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/linker.lds")

add_compile_options(
        #"-pedantic"
        "-O0"
        "-Werror" "-Wall" "-Wextra" "-fmax-errors=5" "-Werror=vla"
        "-Wno-error=unused-parameter"
        "-Wno-error=implicit-fallthrough"
        "-Wno-error=parentheses"
        "-Wno-parentheses"
        "-Wno-unused-parameter"
        "-D_GNU_SOURCE" "-D_TEST_BOOTSTRAP" "-DINSIDE_DANTE")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=output.map")

add_executable(${proj_name}  main.c)
target_link_libraries(${proj_name} m pthread rt)
