# Game template

[![Build](https://github.com/chili-chip/game-template/actions/workflows/build.yml/badge.svg)](https://github.com/chili-chip/game-template/actions/workflows/build.yml)

This is a basic template for starting game projects for VGC Zero, using 32blit sdk. It shows the basic
code layout and asset pipeline, hopefully giving folk a starting point for
any new projects.

It's based on the original `template` project from the 
[32blit-boilerplate](https://github.com/32blit/32blit-boilerplate), with added support for chilichip's vgc zero.

## Getting started

If this is your first 32blit game, follow the [Linux quickstart](https://chilichip.eu/docs/game-sdk/quickstart/linux-quickstart/)
on chilichip.eu first. It installs the toolchain and clones `32blit-sdk`, `pico-sdk` and `pico-extras` next to your game.
CMake 3.28 or newer is needed to use the presets in `CMakePresets.json` (`vgc`, `vgc-blit`, `linux`).

## Usage

[Use this template](https://github.com/chili-chip/game-template/generate) to
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
To build an installable `.blit` for the VGC Zero loader instead of a standalone `.uf2`, add
`-DBLIT_EXECUTABLE_PICO_BLIT=1` to the vgc cmake command (or use the `vgc-blit` preset), then install it over USB with
`32blit install game.blit`. The console needs the loader flashed first; see the
[loader instructions](https://github.com/chili-chip/32blit-sdk/blob/master/docs/vgc.md#loader-and-blit-games-os-preview).

[detailed instructions for vgc](https://github.com/chili-chip/32blit-sdk/blob/master/docs/vgc.md)

Platform and editor specific instructions are in the [32blit SDK fork](https://github.com/chili-chip/32blit-sdk/blob/master/docs/vgc.md)
(for Visual Studio, follow the "Option 2" instructions, as the template does not contain a solution file).

## VS Code Setup (Optional but Recommended)

For the best development experience with VS Code, install these extensions:
- **CMake Tools** - For building and configuring the project with CMake
- **Cortex-Debug** - For debugging on the Pico 2 with OpenOCD

These extensions enable integrated building, flashing, and debugging directly from VS Code.

## Flashing to Pico via SWD

Make sure you have:
- raspberrypi's [openocd fork ](https://github.com/raspberrypi/openocd) installed (rp2350 support not yet in openocd) 
- Pico Debugger or Picoprobe connected via SWD pins (SWDIO, SWCLK, GND)
- The game has been built successfully (produces `game.elf`)


To flash the built executable to your Raspberry Pi Pico using the Pico Debugger over SWD:

```bash
cd build
openocd -f interface/cmsis-dap.cfg -f target/rp2350.cfg -c "adapter speed 5000; program "game.elf" verify reset exit"
```

## Contributing to this template

This repo has two audiences:

- **Making a game?** Click [Use this template](https://github.com/chili-chip/game-template/generate) and work in your
  own repository. Problems with your game belong there.
- **Improving the template itself?** Open an issue or pull request here. Changes that every new game should get belong
  in this repo: build setup, CMake presets, CI, the asset pipeline and these docs. SDK bugs and features go to
  [32blit-sdk](https://github.com/chili-chip/32blit-sdk) instead.

The placeholder name in `LICENSE` is intentional: each game sets its own.
