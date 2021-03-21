# zelda

external libs/tools used :

| library / tool | link                               |
|----------------|------------------------------------|
| imgui          | git submodule                      |
| imgui-SFML     | git submodule                      |
| rapidXML 1.13  | <http://rapidxml.sourceforge.net/> |
| SFML           | git submodule                      |
| Tiled 1.4.3    | <https://thorbjorn.itch.io/tiled>  |

To generate the project, you must define :

| define    | description                                | windows example                      | linux example               |
|-----------|--------------------------------------------|--------------------------------------|-----------------------------|
| IMGUI_DIR | path of the imgui folder in your workspace | D:\Documents\GitHub\zelda\src\imgui\ | /home/gael/zelda/src/imgui/ |

# Visual studio

Don't forget to modify your working directory to $(SolutionDir)

You have an example on how to build with build.cmd

# GCC

Don't forget to launch the executable from it's own directory (to find the copied resources)

You have an example on how to build with build.sh