project("${testName}_task_2")

add_library(hashset hashset.c)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test hashset)
