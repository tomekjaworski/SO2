cmake_minimum_required(VERSION 3.17)
project(processes)

add_subdirectory("spawn0_processh")
add_subdirectory("spawn1_quick")
add_subdirectory("spawn2_long")
add_subdirectory("spawn3_long_wait")


add_subdirectory("ppid")
add_subdirectory("fork1")
add_subdirectory("execl1")
add_subdirectory("execl2_fork")
add_subdirectory("execl3_fork_waitpid")
add_subdirectory("sample_process")

add_subdirectory("fork_sem_shm")
