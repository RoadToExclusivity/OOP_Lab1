@echo off
flipbyte.exe
IF ERRORLEVEL 1 GOTO err

flipbyte.exe notANumber
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe ""
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe -123 > output.txt
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe 2790 > output.txt
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe 0 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt result_for_0.txt
IF ERRORLEVEL 1 GOTO err

flipbyte.exe 6 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt result_for_6.txt
IF ERRORLEVEL 1 GOTO err

flipbyte.exe 209 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt result_for_209.txt
IF ERRORLEVEL 1 GOTO err

flipbyte.exe 255 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt result_for_255.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /b

:err
ECHO Program testing failed :-(
EXIT /b