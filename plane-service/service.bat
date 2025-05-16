@echo off
set service_name=plane-service

if "%1" EQU "-cl" goto clean
if "%1" EQU "-bdl" goto build-docker-less
if "%1" EQU "-bd" goto build-docker
goto end

:clean
echo [script] cleaning %service_name% ...
rd /s /q "build"
echo [script] cleaning %service_name% finished
goto end

:build-docker-less
echo [script] building %service_name% exec ...
call cmake -G "MinGW Makefiles" -B ./build
cd build/
call mingw32-make
cd ../
echo [script] building %service_name% exec finished
goto end

:build-docker
echo [script] building %service_name% image ...
call docker rmi --force $(docker images '%service_name%')
call docker build . -t %service_name%
echo [script] building %service_name% image finished
goto end
















:end
