#!/bin/sh

mkdir build

cd build

cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..

mv GrapesConf.h ../include

ninja

mv src/Grapes ..

rm ../include/GrapesConf.h

cd ..

rm -r build