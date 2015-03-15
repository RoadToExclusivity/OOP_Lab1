@echo off
crypt.exe
IF ERRORLEVEL 1 GOTO err

crypt.exe crypt nofile.in nofile.out 225
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe crypt 1.in 1.out 256
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe crypt 1.in 1.out string
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe wrong_action 1.in 1.out 50
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe crypt 1.in 1.out 44
IF ERRORLEVEL 1 GOTO err
crypt.exe decrypt 1.out 1_1.out 44
IF ERRORLEVEL 1 GOTO err
FC /B 1.in 1_1.out
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /B

:err
ECHO Program testing failed :-(
EXIT /B