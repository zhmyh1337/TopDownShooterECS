#!/bin/bash
PROJECT=${1:-ArcadeSample}
BUILD_TYPE=${2:-rel}
CWD=$(pwd)

cd Builds/ECSCodeGen

./ECSCodeGen-rel.exe $CWD/Common/Sources/Systems $CWD/Projects/$PROJECT/Sources

cd ../..

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

cd Projects
cmake -G Ninja -DPROJECT=$PROJECT -DBUILD_TYPE=$BUILD_TYPE -B ../Builds/unix/$BUILD_TYPE



cd ../Builds/unix/$BUILD_TYPE 
time -p ninja -j $(nproc)

mv Application ../../$PROJECT/$PROJECT-$BUILD_TYPE.exe

cd ../../..


