cmake_minimum_required(VERSION 3.17)
project(upgrade)


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


# -------------

add_subdirectory(shm1-create)
add_subdirectory(shm1-SegVOnWrite)
add_subdirectory(shm1-PROT_EXEC)

add_subdirectory(shm2-client)
add_subdirectory(shm2-server)

add_subdirectory(shm2a-client)
add_subdirectory(shm2a-server)

add_subdirectory(shm3-generator)
add_subdirectory(shm3-sumator)

add_subdirectory(_sandbox)
