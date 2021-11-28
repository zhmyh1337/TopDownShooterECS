@echo off
set PROJECT=%1
set BUILD_TYPE=%2

cd Builds/%PROJECT%
%PROJECT%-%BUILD_TYPE%.exe
cd ../..