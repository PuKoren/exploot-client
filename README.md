exploot-client
==============

The Exploot MMO game client

## Submodules
There is some git submodules to fetch before you go any further
```
git submodule update --init
```
It should clone exploot-protobuf and excellent https://github.com/elvman/RealisticWaterSceneNode
Once cloned, one should run ```build.sh``` script in the ```submodules/exploot-protobuf``` folder (and everytime exploot-protobuf is updated :( I think there is a better way to handle this! Grunt someone?)
Then go to the ```submodules/RealisticWaterSceneNode/RealisticWater.h``` and change ```<irrlicht.h>``` to ```<irrlicht/irrlicht.h>```. A fork may be needed but hey, it's just a one-time edit.

## Dependencies
### Arch Linux
Make sure you have the pacman base-devel installed
```bash
pacman -S irrlicht bullet enet protobuf-c
```

### Windows
If you use Visual Studio, all the crap is pre-configured in the SLN but not maintained, make pull requests if you make it works. Libs are also versionned because maintaining dependencies on Windows is a total brainfuck.

## Compile
### Unix-based systems
Create a build directory inside your sources, like ``mkdir build`` and then ```cd``` into it.
```
cmake ../.
make
```

### Windows
Open .sln with Visual Studio and hit F5
