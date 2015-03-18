@echo off
replace.exe
IF ERRORLEVEL 1 GOTO err

replace.exe no_such_file.txt output.txt awe ee
IF NOT ERRORLEVEL 1 GOTO err

replace.exe 1.txt 1.txt awe ee
IF NOT ERRORLEVEL 1 GOTO err

replace.exe 1.txt output.txt ff ""
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 1_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe 2.txt output.txt qw FTW
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 2_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe 3.txt output.txt getc putc
IF ERRORLEVEL 1 GOTO err
FC /B output.txt 3_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe multiline_text.txt output.txt Hel HEL
IF ERRORLEVEL 1 GOTO err
FC /B output.txt multiline_text_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe recursive.txt output.txt 1231234 abcabcde
IF ERRORLEVEL 1 GOTO err
FC /B output.txt recursive_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe same_text.txt output.txt aa bb
IF ERRORLEVEL 1 GOTO err
FC /B output.txt same_text_out.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /b

:err
ECHO Program testing failed :-(
EXIT /b