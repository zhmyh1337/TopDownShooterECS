cd Projects/ECSCodeGen

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

cd ../..

cmake -G Ninja -DPROJECT=ECSCodeGen -DBUILD_TYPE=rel -B Builds/unix/ECSCodeGen/rel -S Projects/ECSCodeGen


cd Builds/unix/ECSCodeGen/rel 
time -p ninja -j $(nproc)

cd ../../../..