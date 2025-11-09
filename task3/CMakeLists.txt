cmake_minimum_required(VERSION 4.0)
project(Task_3)

include_directories(include)

#основная программа
add_executable(Task_3
        src/Task_3.cpp
        src/testfunc.cpp)

#тесты
add_executable(Task_3_Tests
        tests/test.cpp
        src/testfunc.cpp
)

#заголовки
target_include_directories(Task_3_Tests PRIVATE Task_3/include)
target_link_libraries(Task_3_Tests gtest gtest_main)