#!/bin/sh

#required libs
#libXmu-dev libXi-dev libgl-dev dos2unix git wget

cd ./submodule/glew
make extensions
make glew.lib
echo "Done!"
sleep 5