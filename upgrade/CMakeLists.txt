cmake_minimum_required(VERSION 3.17)
project(my_solution)


add_subdirectory(dll_mutex)

add_subdirectory(heap_asm)
add_subdirectory(heap_sbrk)

add_subdirectory(show1-single)
add_subdirectory(show2-pth)
add_subdirectory(show3-pth2)
add_subdirectory(show4-pth3)
add_subdirectory(show5-join)

add_subdirectory(sem-start)
add_subdirectory(sem-mutex)

add_subdirectory(nsem1-create-exclusive)
add_subdirectory(nsem1-create-reopen)
