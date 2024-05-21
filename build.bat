@echo off
setlocal
set workspaceRoot=%userProfile%\documents\development
set workspaceDir=%~dp0
set workspaceDir=%workspaceDir:~0,-1%

if not exist ./build/bin mkdir "./build/bin"
if not exist ./build/int mkdir "./build/int"

if [%1]==[-d] (
	set ccflags=%ccflags% -DDEBUG
	echo [build]: debug enabled
	echo.
)

set cc=%workspaceRoot%\tinycc.exe
set ccdirs=-B %workspaceRoot%\temp -I %workspaceRoot%\temp\include-extra -I %workspaceDir%\ -L %workspaceRoot%\temp\lib-extra 
set ccflags=%ccflags% -O2
set cclibs=-lws2_32

%cc% %ccdirs% %ccflags% -c -o %workspaceDir%\build\int\entrypoint.o %workspaceDir%\src\entrypoint.c
%cc% %ccdirs% %ccflags% -c -o %workspaceDir%\build\int\http.o %workspaceDir%\src\http.c
%cc% %ccdirs% -o %workspaceDir%\build\bin\pixelproxy.exe %workspaceDir%\build\int\*.o %cclibs%

endlocal