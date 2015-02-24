@echo off
replace.exe
IF ERRORLEVEL 1 GOTO err

replace.exe no_such_file.txt output.txt awe ee
IF NOT ERRORLEVEL 1 GOTO err

replace.exe 1.in output.txt ff ""
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 1.out
IF ERRORLEVEL 1 GOTO err

replace.exe 2.in output.txt qw FTW
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 2.out
IF ERRORLEVEL 1 GOTO err

replace.exe 3.in output.txt getc putc
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 3.out
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /b

:err
ECHO Program testing failed :-(
EXIT /b