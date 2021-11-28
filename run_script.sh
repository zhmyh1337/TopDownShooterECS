#!/bin/bash
PROJECT=${1:-ArcadeSample}
BUILD_TYPE=${2:-rel}

cd ./Builds/$PROJECT
./$PROJECT-$BUILD_TYPE.exe
cd ../..
