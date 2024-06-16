@echo off
setlocal

call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\vsdevcmd.bat"

cl /c /EHsc .\DLL\CaesarCifer.cpp
if %ERRORLEVEL% neq 0 echo Build failed.

cl /LD .\CaesarCifer.obj /Fe:.\CaesarCifer.dll
if %ERRORLEVEL% neq 0 echo Build failed.

dumpbin /exports .\CaesarCifer.dll
if %ERRORLEVEL% neq 0 echo Build failed.

cl /EHsc .\TextEditor\Program.cpp /link .\CaesarCifer.lib /out:TextEditor.exe
if %ERRORLEVEL% neq 0 echo Build failed.

echo Build succeeded.

pause
endlocal
