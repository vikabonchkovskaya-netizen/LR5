@echo off
REM -------------------------------
REM Build script for LR5 project
REM -------------------------------

REM 1. Папка сборки
if not exist build (
    mkdir build
)

REM 2. Проверка где лежат исходники
if exist src\RecDLL.cpp (
    set DLL_SRC=src\RecDLL.cpp
) else if exist RecDLL.cpp (
    set DLL_SRC=RecDLL.cpp
) else (
    echo Error: RecDLL.cpp not found!
    pause
    exit /b
)

if exist src\Task_2.cpp (
    set EXE_SRC=src\Task_2.cpp
) else if exist Task_2.cpp (
    set EXE_SRC=Task_2.cpp
) else (
    echo Error: Task_2.cpp not found!
    pause
    exit /b
)

REM 3. Компиляция DLL
echo Compiling DLL...
g++ -shared -o build/RecDLL.dll %DLL_SRC% -Iinclude -DMINLIBRARY_EXPORTS
if errorlevel 1 (
    echo DLL compilation failed!
    pause
    exit /b
)

REM 4. Компиляция exe
echo Compiling main executable...
g++ -o build/Task_2.exe %EXE_SRC% -Iinclude
if errorlevel 1 (
    echo EXE compilation failed!
    pause
    exit /b
)

REM 5. Копируем DLL рядом с exe (для LoadLibrary)
copy /Y build\RecDLL.dll build\Task_2.exe >nul

echo Build completed successfully!
echo Run the program: build\Task_2.exe
pause
