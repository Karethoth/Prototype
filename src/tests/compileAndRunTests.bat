@echo off
:start
echo Creating tests.cc
call ..\..\..\cxxtest\bin\cxxtestgen --error-printer -o tests.cc main.cc
echo Compiling tests.cc
call g++ -std=c++11 -o run tests.cc -lpthreadGC2
echo Running tests
call run.exe

pause