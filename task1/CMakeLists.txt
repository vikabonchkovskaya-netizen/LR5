cmake_minimum_required(VERSION 3.16)
project(Task1_Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)  # только статическая библиотека

# === Библиотека ===
add_library(MatrixDLL STATIC
    src/MatrixDLL.cpp
)
target_include_directories(MatrixDLL PUBLIC ${CMAKE_SOURCE_DIR}/include)

# === Исполняемый файл ===
add_executable(Task_1 src/Task_1.cpp)
target_include_directories(Task_1 PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Task_1 PRIVATE MatrixDLL)

# === Google Test ===
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_task1_simple tests/test_task1_simple.cpp)
target_include_directories(test_task1_simple PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_task1_simple PRIVATE MatrixDLL gtest_main)

include(GoogleTest)
gtest_discover_tests(test_task1_simple)
