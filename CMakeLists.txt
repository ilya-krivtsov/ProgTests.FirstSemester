cmake_minimum_required(VERSION 3.20)
project(tests LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_subdirectory(test_1_1)
add_subdirectory(test_1_2)
add_subdirectory(test_2_1)
add_subdirectory(test_2_2)
add_subdirectory(test_final)
add_subdirectory(test_final_1)
