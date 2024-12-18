project("${testName}_task_2")

add_library(stackQueue stackQueue.c)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test stackQueue)
