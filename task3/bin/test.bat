@echo off
invert.exe
IF ERRORLEVEL 1 GOTO err

invert.exe ""
IF NOT ERRORLEVEL 1 GOTO err

invert.exe no_such_file.txt
IF NOT ERRORLEVEL 1 GOTO err

invert.exe wrong_matrix.txt
IF NOT ERRORLEVEL 1 GOTO err

invert.exe 1.in > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 1.out
IF ERRORLEVEL 1 GOTO err

invert.exe 2.in > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 2.out
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT