@echo off
replace.exe
IF ERRORLEVEL 1 GOTO err

replace.exe no_such_file.txt output.txt awe ee
IF NOT ERRORLEVEL 1 GOTO err

replace.exe multiline_text.txt output.txt "" HEL
IF NOT ERRORLEVEL 1 GOTO err

replace.exe multiline_text.txt output.txt Hel HEL
IF ERRORLEVEL 1 GOTO err
FC /B output.txt multiline_text_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe recursive.txt output.txt 1231234 abcabcde
IF ERRORLEVEL 1 GOTO err
FC /B output.txt recursive_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe recursive.txt output.txt 1 ""
IF ERRORLEVEL 1 GOTO err
FC /B output.txt recursive_with_delete_out.txt
IF ERRORLEVEL 1 GOTO err

replace.exe repeated_text.txt output.txt aa a
IF ERRORLEVEL 1 GOTO err
FC /B output.txt repeated_text_out.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT /b

:err
ECHO Program testing failed :-(
EXIT /b