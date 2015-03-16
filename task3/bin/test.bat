@echo off
invert.exe
IF ERRORLEVEL 1 GOTO err

invert.exe ""
IF NOT ERRORLEVEL 1 GOTO err

invert.exe NO_SUCH_FILE.txt
IF NOT ERRORLEVEL 1 GOTO err

invert.exe WrongMatrix.txt
IF NOT ERRORLEVEL 1 GOTO err

invert.exe MatrixWithFloatNumbers.txt > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt MatrixWithFloatNumbers_out.txt
IF ERRORLEVEL 1 GOTO err

invert.exe MatrixWithIntegerNumbers.txt > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt MatrixWithIntegerNumbers_out.txt
IF ERRORLEVEL 1 GOTO err

invert.exe MatrixWithZeroDeterminant.txt > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt MatrixWithZeroDeterminant_out.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /b

:err
ECHO Program testing failed :-(
EXIT /b