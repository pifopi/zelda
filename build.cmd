pushd %~dp0

mkdir bin
cd bin
cmake ../src -G "Visual Studio 15 2017 Win64" -DCMAKE_MODULE_PATH=C:/SFML/2.4.2 -DSFML_ROOT=C:/SFML/2.4.2
MSBuild.exe .\main.vcxproj /p:Configuration=Debug
MSBuild.exe .\main.vcxproj /p:Configuration=Release
MSBuild.exe .\main.vcxproj /p:Configuration=RelWithDebInfo
MSBuild.exe .\main.vcxproj /p:Configuration=MinSizeRel

popd
