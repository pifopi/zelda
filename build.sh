SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")

mkdir bin
cd bin
mkdir Debug
mkdir Release
mkdir RelWithDebInfo
mkdir MinSizeRel
cd Debug
cmake ../../src/ -DIMGUI_DIR=$SCRIPTPATH/src/imgui/ -DCMAKE_BUILD_TYPE=Debug
make
cd ../Release
cmake ../../src/ -DIMGUI_DIR=$SCRIPTPATH/src/imgui/ -DCMAKE_BUILD_TYPE=Release
make
cd ../RelWithDebInfo
cmake ../../src/ -DIMGUI_DIR=$SCRIPTPATH/src/imgui/ -DCMAKE_BUILD_TYPE=RelWithDebInfo
make
cd ../MinSizeRel
cmake ../../src/ -DIMGUI_DIR=$SCRIPTPATH/src/imgui/ -DCMAKE_BUILD_TYPE=MinSizeRel
make
