@echo off
REM TODO check %GOROOT%

set GOBIN = %GOROOT%\bin
set GOARCH=386
set GOOS=windows

PATH = %GOROOT%\bin;%PATH%
@echo on

8g -o obj\server.8 server\server.go 
8l -o server.exe obj\server.8