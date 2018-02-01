mkdir bin
cd bin
mkdir Debug
mkdir Release
mkdir RelWithDebInfo
mkdir MinSizeRel
cd Debug
cmake ../../src -DCMAKE_MODULE_PATH=/home/gael/SFML/2.4.2/ -DSFML_ROOT=/home/gael/SFML/2.4.2/ -DCMAKE_BUILD_TYPE=Debug
make
cd ../Release
cmake ../../src -DCMAKE_MODULE_PATH=/home/gael/SFML/2.4.2/ -DSFML_ROOT=/home/gael/SFML/2.4.2/ -DCMAKE_BUILD_TYPE=Release
make
cd ../RelWithDebInfo
cmake ../../src -DCMAKE_MODULE_PATH=/home/gael/SFML/2.4.2/ -DSFML_ROOT=/home/gael/SFML/2.4.2/ -DCMAKE_BUILD_TYPE=RelWithDebInfo
make
cd ../MinSizeRel
cmake ../../src -DCMAKE_MODULE_PATH=/home/gael/SFML/2.4.2/ -DSFML_ROOT=/home/gael/SFML/2.4.2/ -DCMAKE_BUILD_TYPE=MinSizeRel
make
