@echo off

cmake --preset vs2019-windows || goto :error
cmake --build build --config Release --target PACKAGE || goto :error

cmake --preset vs2019-windows-vr || goto :error
cmake --build buildVR --config Release --target PACKAGE || goto :error

goto :EOF

:error
exit /b %ERRORLEVEL%
