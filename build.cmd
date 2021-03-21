pushd %~dp0

mkdir bin
cd bin
cmake ../src/ -G "Visual Studio 16" -DIMGUI_DIR=%~dp0/src/imgui/
MSBuild.exe .\main.vcxproj /p:Configuration=Debug
MSBuild.exe .\main.vcxproj /p:Configuration=Release
MSBuild.exe .\main.vcxproj /p:Configuration=RelWithDebInfo
MSBuild.exe .\main.vcxproj /p:Configuration=MinSizeRel

popd
