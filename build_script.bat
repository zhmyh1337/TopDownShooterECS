@echo off
set PROJECT=%1
set BUILD_TYPE=%2


set CWD=%cd%

cd Builds/ECSCodeGen
ECSCodeGen-rel.exe %CWD%/Projects/Common/Sources/Systems %CWD%/Projects/%PROJECT%/Sources
cd ../..

cd Projects
cmake -G Ninja -DPROJECT=%PROJECT% -DBUILD_TYPE=%BUILD_TYPE% -B ../Builds/win/%BUILD_TYPE%
cd ../Builds/win/%BUILD_TYPE% 

ninja

set binPath=..\..\%PROJECT%
IF not exist %binPath% (mkdir %binPath%)

ren Application.exe %PROJECT%-%BUILD_TYPE%.exe

move %PROJECT%-%BUILD_TYPE%.exe %binPath%

cd ../../..