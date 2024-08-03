# DIY soldering station firmware
## Help functions
The command ```make help``` gives an overview of various help commands:
* ```make projects``` gives a list of available projects
* ```make libraries``` gives a list of available libraries
* passing the variable ```VERBOSE=1``` gives full command output
## Project list
Running the command ```make projects``` gives an overview of the projects available.
* PC: PC empty project
* DIYSOLDER_LPC845: DIY soldering station firmware with LPC845 microcontroller
## Building
The ```projects``` directory contains all the projects. Invoking compilation of any project is done with the ```PROJECT``` variable that needs to be passed on, see the following example:
```
make PROJECT=PC
```
Building can be done with various configurations that set up flags and other settings, this configuration is set with the ```CONFIG``` variable. Most projects have the ```release``` and ```debug``` where the ```debug``` configuration is default.
The ```release``` configuration has optimizations enabled (usually for size) and minimal included debugging information. The ```debug``` configuration has NO optimization and full debugging information. There might be specific configurations available per project.
For cleaning execute the following command:
```
make clean
```
### Debugging embedded projects
For debugging on embedded targets, the [Black Magic Probe](https://github.com/blacksphere/blackmagic/wiki) is used, scripts to use this debugger are present in the ```gdb_scripts``` directory. make can be used to invoke debugging:
```
make gdbbmp
```
This will build, if needed, the debug build and load it into the target.
### Depedencies
The templates have a few dependencies that are automatically cloned when you do a clone with ```--recurses-submodules```
* squantorLibC for minimal LibC functionality
* squantorLibEmbedded for various helper functions
## Usage
To use the software you need the following hardware:
* [Black magic probe](https://github.com/blacksphere/blackmagic)
* gnu make
* [Visual Studio Code](https://code.visualstudio.com/) with c/c++ language support and [Cortex-debug](https://github.com/Marus/cortex-debug) for debugging embedded targets
* [compiledb](https://github.com/nickdiego/compiledb)
