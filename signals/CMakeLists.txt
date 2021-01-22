cmake_minimum_required(VERSION 3.17)
project(signals)


add_subdirectory("p_signal_receiver")
add_subdirectory("p_signal_receiver_simple")
add_subdirectory("p_signal_receiver_SEGV")
add_subdirectory("p_signal_receiver_multithread")


add_subdirectory("p_alarm")

add_subdirectory("p_signal_sender_sigqueue_simple")
add_subdirectory("p_signal_sender_sigqueue")
add_subdirectory("p_signal_sender_kill")

add_subdirectory("sem_wait_interrupt_singlethread")
add_subdirectory("sem_wait_interrupt_multithreaded")