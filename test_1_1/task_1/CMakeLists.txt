project("${testName}_task_1")

add_library(intPalindrome intPalindrome.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} intPalindrome)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test intPalindrome)
