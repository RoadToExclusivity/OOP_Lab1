@echo off
fill.exe
IF ERRORLEVEL 1 GOTO err

fill.exe nofile.txt out.txt
IF NOT ERRORLEVEL 1 GOTO err

fill.exe fill.txt out.txt
IF ERRORLEVEL 1 GOTO err
FC /B out.txt fill_out.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /B

:err
ECHO Program testing failed :-(
EXIT /B