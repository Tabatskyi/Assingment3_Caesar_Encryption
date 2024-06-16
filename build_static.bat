@echo off
setlocal

call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\vsdevcmd.bat"

cl /c /EHsc .\TextEditor\CaesarCiferStatic.cpp
if %ERRORLEVEL% neq 0 echo Build failed.

lib CaesarCiferStatic.obj
if %ERRORLEVEL% neq 0 echo Build failed.

cl /EHsc .\TextEditor\Program_static.cpp .\TextEditor\Memory.cpp .\TextEditor\Append.cpp .\TextEditor\NewLine.cpp .\TextEditor\SaveToFile.cpp .\TextEditor\LoadFromFile.cpp .\TextEditor\Insert.cpp .\TextEditor\Delete.cpp .\TextEditor\Copy.cpp .\TextEditor\Cut.cpp .\TextEditor\Paste.cpp .\TextEditor\Replace.cpp .\TextEditor\Coursor.cpp /link .\CaesarCiferStatic.lib /out:TextEditor.exe
if %ERRORLEVEL% neq 0 echo Build failed.

echo Build succeeded.

pause
endlocal
