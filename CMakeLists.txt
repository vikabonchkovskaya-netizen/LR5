cmake_minimum_required(VERSION 3.10)
project(MatrixTests)

# Настройка компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для Windows
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(BUILD_SHARED_LIBS ON)
endif()

# Включение Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.7.0.zip
)
FetchContent_MakeAvailable(googletest)

# === ЗАДАЧА 5 ===
# DLL для задачи 5
add_library(MatrixDLL_task5 SHARED
    task5/src/MatrixDLL.cpp
    # Добавьте другие исходные файлы задачи 5 здесь
)

# Исполняемый файл тестов для задачи 5
add_executable(test_task5
    task5/tests/test_task5.cpp
)

target_link_libraries(test_task5 MatrixDLL_task5 gtest gtest_main)

# Копируем DLL рядом с исполняемым файлом
add_custom_command(TARGET test_task5 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:MatrixDLL_task5>
    $<TARGET_FILE_DIR:test_task5>
)
# === ЗАДАЧА 4 ===
# DLL для задачи 4
add_library(MatrixDLL_task4 SHARED
    task4/src/MatrixDLL.cpp
    # Добавьте другие исходные файлы задачи 4 здесь
)

# Исполняемый файл тестов для задачи 4
add_executable(test_task4
    task4/tests/test_task4.cpp
)

target_link_libraries(test_task4 MatrixDLL_task4 gtest gtest_main)

# Копируем DLL рядом с исполняемым файлом
add_custom_command(TARGET test_task4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:MatrixDLL_task4>
    $<TARGET_FILE_DIR:test_task4>
)