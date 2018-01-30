# zelda

external libs/tools used :

| library / tool | link                                       |
|----------------|--------------------------------------------|
| imgui          | <https://github.com/ocornut/imgui>         |
| imgui-SFML     | <https://github.com/eliasdaler/imgui-sfml> |
| rapidXML 1.13  | <http://rapidxml.sourceforge.net/>         |
| SFML 2.4.2     | <https://www.sfml-dev.org/index-fr.php>    |
| Tiled 1.0.3    | <https://thorbjorn.itch.io/tiled>          |

To generate the project, you must define :

| define            | description                             | windows example | linux example          |
|-------------------|-----------------------------------------|-----------------|------------------------|
| CMAKE_MODULE_PATH | path of the file "FindSFML.cmake"       | C:/SFML/2.4.2   | /home/gael/SFML/2.4.2/ |
| SFML_ROOT         | path of your installation of SFML 2.4.2 | C:/SFML/2.4.2   | /home/gael/SFML/2.4.2/ |

# Visual studio

Don't forget to modify your working directory to $(SolutionDir)

# GCC

Don't forget to launch the executable from it's own directory (to find the copied resources)

Here is an example of the command line I do to set up the project

```
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
```