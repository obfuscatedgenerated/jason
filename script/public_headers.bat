@echo off

rem argument 1: path to include dir
rem argument 2: path to output dir

rem copy include files to output dir but for each file:
rem - dont copy if the file is named "lib_def.h"
rem - dont copy if the first line of the file ends with #PRIVATEHEADER
rem - remove #include directives that include a file named "lib_def.h at any level (e.g. #include "lib_def.h", #include "./lib_def.h", #include "../lib_def.h")
rem - if a line starts with PUBLIC, remove the PUBLIC keyword
rem - if a line starts with PRIVATE, remove the whole line
rem - if a line ends with #PRIVATE, remove the whole line

set INCLUDE_DIR=%1
set OUTPUT_DIR=%2
set TEMP_DIR=%OUTPUT_DIR%\include\temp

if not exist "%OUTPUT_DIR%\include" mkdir "%OUTPUT_DIR%\include"
if not exist "%TEMP_DIR%" mkdir "%TEMP_DIR%"

rem copy include dir to output dir
xcopy /e /i /y "%INCLUDE_DIR%" "%OUTPUT_DIR%\include"

rem remove lib_def.h
del "%OUTPUT_DIR%\include\lib_def.h"

setlocal enabledelayedexpansion

for /r "%OUTPUT_DIR%\include" %%f in (*.h) do (
        rem remove file if the first line of the file ends with #PRIVATEHEADER
        set /p firstline=<"%%f"
        if "!firstline:#PRIVATEHEADER=!" neq "!firstline!" (
                del "%%f"
        ) else (
            rem remove #include directives that include a file named "lib_def.h at any level
            type "%%f" | findstr /v /c:"lib_def.h" > "%TEMP_DIR%\temp.h"
            rem replace the word PUBLIC followed by space with nothing if it is at the beginning of a line using substrings
            for /f "tokens=1,* delims=:" %%i in ('findstr /n "^" "%TEMP_DIR%\temp.h"') do (
                    set "line=%%j"
                    if "!line:~0,6!"=="PUBLIC" (
                            set "line=!line:PUBLIC =!"
                    )
                    echo(!line!>>"%TEMP_DIR%\temp2.h"
            )
            rem remove lines starting with PRIVATE (the whole line)
            type "%TEMP_DIR%\temp2.h" | findstr /v /b /c:"PRIVATE" > "%TEMP_DIR%\temp3.h"
            rem remove lines ending with #PRIVATE (the whole line)
            type "%TEMP_DIR%\temp3.h" | findstr /v /e /c:"#PRIVATE" > "%TEMP_DIR%\temp4.h"
            rem copy result to file
            copy /y "%TEMP_DIR%\temp4.h" "%%f"
            rem delete temporary files
            del "%TEMP_DIR%\temp.h"
            del "%TEMP_DIR%\temp2.h"
            del "%TEMP_DIR%\temp3.h"
            del "%TEMP_DIR%\temp4.h"
        )
)

rmdir /s /q "%TEMP_DIR%"

rem check errorlevel (so not accidentally erased later)
if errorlevel 1 exit /b 1

rem delete any empty directories in the output dir include
for /f "delims=" %%d in ('dir /s /b /ad "%OUTPUT_DIR%\include" ^| sort /r') do rd "%%d" 2>nul

rem clear any errorlevel set by the above command
cmd /c exit 0
