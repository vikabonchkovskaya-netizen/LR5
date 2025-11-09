cmake_minimum_required(VERSION 4.0)
project(Task_2)

include_directories(include)

#основная программа
add_executable(Task_2
        src/task_2.cpp
        src/testfunc.cpp)

#тесты
add_executable(Task_2_Tests
        tests/test.cpp
        src/testfunc.cpp
)

#заголовки
target_include_directories(Task_2_Tests PRIVATE Task_2/include)
target_link_libraries(Task_2_Tests gtest gtest_main)