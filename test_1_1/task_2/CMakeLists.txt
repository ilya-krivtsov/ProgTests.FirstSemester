project("${testName}_task_2")

add_library(bogosort bogosort.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} bogosort)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test bogosort)
