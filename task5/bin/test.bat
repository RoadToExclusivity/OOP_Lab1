@echo off
crypt.exe
IF ERRORLEVEL 1 GOTO err

crypt.exe crypt nofile.in nofile.out 225
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe crypt simple_text.txt out.txt 256
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe crypt simple_text.txt out.txt string
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe wrong_action simple_text.txt out.txt 50
IF NOT ERRORLEVEL 1 GOTO err

crypt.exe crypt simple_text.txt out.txt 44
IF ERRORLEVEL 1 GOTO err
crypt.exe decrypt out.txt simple_text_out.txt 44
IF ERRORLEVEL 1 GOTO err
FC /B simple_text.txt simple_text_out.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /B

:err
ECHO Program testing failed :-(
EXIT /B