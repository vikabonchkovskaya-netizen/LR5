@echo off
REM =====================================================
REM   Сборка DLL + Google Test + тестов для task4
REM =====================================================

REM Создаём папку build, если её нет
if not exist build mkdir build

echo ==============================
echo 1. Компиляция Google Test
echo ==============================
g++ -std=c++17 -Wall -Igoogletest-release-1.7.0/include -Igoogletest-release-1.7.0 ^
-c googletest-release-1.7.0/src/gtest-all.cc -o build/gtest-all.o

echo ==============================
echo 2. Компиляция DLL
echo ==============================
g++ -std=c++17 -Wall -Itask4/include -c task4/src/MatrixDLL.cpp -o build/MatrixDLL_task4.o
g++ -shared -o build/MatrixDLL_task4.dll build/MatrixDLL_task4.o -Wl,--out-implib,build/libMatrixDLL_task4.a

echo ==============================
echo 3. Компиляция теста
echo ==============================
g++ -std=c++17 -o build/test_task4.exe task4/tests/test_task4.cpp build/gtest-all.o -Igoogletest-release-1.7.0/include -Igoogletest-release-1.7.0 -Lbuild -static-libgcc -static-libstdc++ -mconsole

echo ==============================
echo 4. Копируем DLL в папку с тестом
echo ==============================
copy build\MatrixDLL_task4.dll build\

echo ==============================
echo 5. Запуск тестов
echo ==============================
cd build
test_task4.exe

pause
