cmake_minimum_required(VERSION 3.17)
project(processes)


add_subdirectory("ppid")
add_subdirectory("fork1")
add_subdirectory("spawn1")
add_subdirectory("execl1")
add_subdirectory("execl2_fork")
add_subdirectory("execl3_fork_waitpid")
add_subdirectory("spawn2_wait")
add_subdirectory("sample_process")

add_subdirectory("fork_sem_shm")
