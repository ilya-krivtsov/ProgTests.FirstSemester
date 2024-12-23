project("${testName}_task_3")

add_library(commentsExtractor commentsExtractor.c)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test commentsExtractor)
