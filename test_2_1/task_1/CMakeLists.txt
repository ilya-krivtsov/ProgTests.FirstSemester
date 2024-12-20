project("${testName}_task_1")

add_library(fileParser fileParser.c)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test fileParser)
