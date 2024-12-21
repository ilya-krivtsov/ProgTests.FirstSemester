project("${testName}_task_1")

add_library(binaryToDecimal binaryToDecimal.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} binaryToDecimal)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test binaryToDecimal)
