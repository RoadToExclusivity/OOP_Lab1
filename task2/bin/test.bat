@echo off
lab1_2.exe
IF ERRORLEVEL 1 GOTO err

LAB1_2.exe notANumber
IF NOT ERRORLEVEL 1 GOTO err

lab1_2.exe ""
IF NOT ERRORLEVEL 1 GOTO err

lab1_2.exe -123 > output.txt
IF NOT ERRORLEVEL 1 GOTO err

lab1_2.exe 6 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 1.txt
IF ERRORLEVEL 1 GOTO err

lab1_2.exe 209 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 2.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT