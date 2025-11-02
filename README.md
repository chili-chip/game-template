# Game template

![Build](https://github.com/chili-chip/32blit-boilerplate/workflows/Build/badge.svg)

This is a basic template for starting game projects for VGC Zero, using 32blit sdk. It shows the basic
code layout and asset pipeline, hopefully giving folk a starting point for
any new projects.

It's based on the original `template` project from the 
[32blit-boilerplate](https://github.com/32blit/32blit-boilerplate), with added support for chilichip's vgc zero.

## Usage

[Use this template](https://github.com/chili-chip/32blit-boilerplate/generate) to
generate your own project.

* Edit the CMakeList.txt file to set the name of your project
* Edit the metadata.yml file to set the information for your project
* Edit the LICENSE file to set your name on the license
* Write lots of super cool code!

You should then be able to follow the usual build instructions.

For local builds this is:
```
mkdir build
cd build
cmake -D32BLIT_DIR=/path/to/32blit-sdk/ ..
```

For vgc zero builds this is:
```
mkdir build.vgc
cd build.vgc
cmake .. \
  -D32BLIT_DIR=../../32blit-sdk \
  -DPICO_SDK_PATH=../../pico-sdk \
  -DPICO_BOARD=chilichip_vgc \
  -DPICO_PLATFORM=rp2350-arm-s \
  -DCMAKE_TOOLCHAIN_FILE=../../32blit-sdk/pico2.toolchain
```
[detailed instructions for vgc](https://github.com/chili-chip/32blit-sdk/blob/master/docs/vgc.md)

Platform/Editor specific insctuctions [can be found in the fork of the main 32blit repo](https://github.com/chili-chip/32blit-sdk/blob/master/docs/vgc.md)
(For Visual Studio, you should follow the "Option 2" instructions, as the boilerplate does not contain a solution file)
