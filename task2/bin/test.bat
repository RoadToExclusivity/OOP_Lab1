@echo off
flipbyte.exe
IF ERRORLEVEL 1 GOTO err

flipbyte.exe notANumber
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe ""
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe -123 > output.txt
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe 6 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 1.txt
IF ERRORLEVEL 1 GOTO err

flipbyte.exe 209 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 2.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT