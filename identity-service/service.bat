@echo off
set service_name=identity-service

if "%1" EQU "-cl" goto clean
if "%1" EQU "-bdl" goto build-docker-less
if "%1" EQU "-bd" goto build-docker
goto end

:clean
echo [script] cleaning %service_name% ...
call gradlew clean
rd /s /q ".gradle"
echo [script] cleaning %service_name% finished
goto end

:build-docker-less
echo [script] building %service_name% exec ...
call gradlew clean
rd /s /q ".gradle"
call gradlew bootJar
echo [script] building %service_name% exec finished
goto end

:build-docker
echo [script] building %service_name% image ...
call docker rmi --force $(docker images '%service_name%')
call docker build . -t %service_name%
echo [script] building %service_name% image finished
goto end
















:end
