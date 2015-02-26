@echo off
bmpinfo.exe
IF ERRORLEVEL 1 GOTO err

bmpinfo.exe ""
IF NOT ERRORLEVEL 1 GOTO err

bmpinfo.exe no_such_file.bmp
IF NOT ERRORLEVEL 1 GOTO err

bmpinfo.exe 1.bmp > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 1.out
IF ERRORLEVEL 1 GOTO err

bmpinfo.exe 2.bmp > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 2.out
IF ERRORLEVEL 1 GOTO err

bmpinfo.exe 3.bmp
IF NOT ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /B

:err
ECHO Program testing failed :-(
EXIT /B