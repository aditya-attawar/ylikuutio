# Ylikuutio. A 3D game and simulation engine.
A hobby project of mine. Work in progress.

[![Build status](https://travis-ci.org/nrz/ylikuutio.svg?branch=master)](https://travis-ci.org/nrz/ylikuutio)
[![Coverity Scan](https://scan.coverity.com/projects/nrz-ylikuutio/badge.svg)](https://scan.coverity.com/projects/nrz-ylikuutio)

## License
Ylikuutio is under The GNU Affero General Public License 3,
or (at your option) any later version. See COPYING file.
All my code copyright (C) 2015-2018 Antti Nuortimo.

## Overview
Ylikuutio is a 3D game engine designed for 3D games and simulations.
Ylikuutio aims to run fast and support also older hardware.
Currently Ylikuutio works on 64-bit Linux and Windows systems.
Android support is a work in progress.

## Compiling
Ylikuutio can be compiled with GCC, Clang or Visual Studio.
In Visual Studio compiling may break due to compiler-specific bugs.
Cross compiling from Linux® to Windows using MinGW-w64 works fine.
C++14 support is required.
OpenGL 3.0 or newer is required.
CMake 2.6.2 or newer is needed for the compiling process.
CMake uses git for downloading Google Test testing framework.

Ylikuutio repository in GitHub has 2 branches: `master` & `coverity_scan`.
master is the branch that should be up to date and it's the one to build.
`coverity_scan` is for Synopsys© Coverity Scan© analysis tool which is run through
Travis CI. However, Coverity Scan analysis tool configuration in `.travis.yml`
is not yet ready and does not yet work.

In Linux it's simple.

First, install all the necessary compilers, tools and libs. You may use
your favorite package manager such as apt, aptitude, apt-get, yum etc.
You all need these packages: cmake make g++ gcc libx11-dev libgl1-mesa-dev libglu1-mesa-dev libsfml-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev
Eg. with apt:

    $ sudo apt install cmake build-essential libx11-dev libgl1-mesa-dev libglu1-mesa-dev libsfml-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev

If you are doing a cross compile from Linux to Windows, you need also:

    $ sudo apt install g++-mingw-w64 gcc-mingw-w64 binutils-mingw-w64

If you are doing a cross compile from Linux to Android™, you need also:

    $ sudo apt install google-android-ndk-installer

However, cross compiling from Linux to Android does not work yet!

Then, to compile with GCC, in Ylikuutio install directory:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

To make compiling faster you probably want to use several threads:

    $ make -j $(($(nproc) - 1))

Or, to compile with Clang, again in Ylikuutio install directory:

    $ mkdir build
    $ cd build
    $ export CC="$(which clang)"
    $ export CXX="(which clang++)"
    $ cmake ..
    $ make

If you have problems compiling tests or for some other reason don't want
to compile tests, in CMakeLists.txt comment out the line that says:
`set(DO_UNIT_TESTS_WITH_GOOGLE_TEST true)`

To cross compile from Linux to Windows:

    $ mkdir build_windows
    $ cd build_windows
    $ cmake -DCMAKE_TOOLCHAIN_FILE=../w64.cmake ..
    $ make

Crosscompiling from Linux to Windows fails to compile tests.
This is a known bug in Google Test. Just run `make` *again* if
compiling ends before you get `ajokki.exe` and `tinyscheme_test.exe`.
You can also disable compiling of tests as described above.
https://github.com/google/googletest/issues/606

To cross compile from Linux to Android (using Android NDK):

    $ mkdir build_android
    $ cd build_android
    $ cmake -DCMAKE_TOOLCHAIN_FILE=../android.cmake ..
    $ make

However, cross compiling from Linux to Android does not work yet!

Compiling in Visual Studio is more difficult. The recommended way to
get a binary for Windows is to cross compile from Linux to Windows.

To run Ajokki (working title based on Finnish bus body manufacturer),
a demo program to check out some properties of Ylikuutio 3D engine:

In Linux:

    $ ./ajokki

In Windows:

    > ajokki.exe

`ajokki.exe` binary can also be executed in Linux, using Wine:

    $ wine ./ajokki.exe

Press `` to get console. Press F to toggle flying on off.
Arrow keys work too. Ctrl is turbo. F1 toggles help display
and there you'll see some more options to try.

To run tests (coverage is still quite limited but underway):

    $ ./unit_tests_with_Google_Test

## Ylikuutio usage
This part reflects the current usage of Ylikuutio and will change as new
functionality is implemented.

At the moment, you need a `main` function (for an example, please see
`code/ajokki/ajokki.cpp`) which starts your game/simulation (initialization),
runs the game/simulation (the main loop) and ends the program (cleaning-up).
In all these phases mentioned above Ylikuutio library functions may be used.
Ylikuutio library code is located in `code/ylikuutio/` tree. Ylikuutio code
may change a lot and so far no API has been defined. Ajokki and Ylikuutio
code itself are the best references on how to use Ylikuutio in practice.

Some available console commands to try in Ajokki:
* `activate joensuu_center_and_west_scene`
* `activate helsinki_east_downtown_scene`
* `activate altiplano_scene`
* `set red 1.0`
* `set green 0.15`
* `set blue 0.77`
* `get red`
* `get green`
* `get blue`
* `set x 123`
* `set y 456`
* `set z 789`
* `get x`
* `get y`
* `get z`
* `info`
* `info cat_species`
* `info cat2`
* `set wireframe true`
* `set wireframe false`
* `get turbo_polizei1 cartesian_coordinates`
* `get turbo_polizei1 x`
* `get turbo_polizei1 y`
* `get turbo_polizei1 z`
* `set turbo_polizei1 y 50`
* `set turbo_polizei1 x 100`
* `set turbo_polizei1 z 200`
* `get cat1 cartesian_coordinates`
* `get cat1 x`
* `get cat1 y`
* `get cat1 z`
* `set cat1 x 123.45`
* `set cat1 z 210`

## FAQ
Q: What is "Ylikuutio"?
A: In Finnish, "yli" means ["over"](https://en.wiktionary.org/wiki/yli-), and "kuutio" means ["cube"](https://en.wiktionary.org/wiki/kuutio).
   So, "Ylikuutio" is a reference to a [hypercube](https://en.wikipedia.org/wiki/Hypercube).

Q: How is Ylikuutio software developed?
A: In [Debian GNU/Linux](https://www.debian.org/) ([Debian Stretch](https://wiki.debian.org/DebianStretch) at the moment), using [Vim](http://www.vim.org/).

Q: For what kinds of software Ylikuutio can be used?
A: Ylikuutio can be used for all kinds of 3D games and simulations.
   At the moment no specific support for 2D is available, but naturally
   3D graphics can also be used to present a 2D world.

Q: What are the design goals for Ylikuutio?
A: Ylikuutio aims to be a fast and flexible 3D game/simulation engine
   and fulfil my own requirements for my own indie game projects.
   Ylikuutio aims to run fast also on low-end video cards.
   Higher detail level may be offered for high-end video cards.

Q: What are the target platforms of Ylikuutio?
A: Ylikuutio targets Linux, Windows and Android, in this order.
   Cross-compiling from Linux to Windows works!
   Cross-compiling from Linux to Android is not implemented yet.
   Currently only 64-bit environments are supported.

Q: What graphics APIs Ylikuutio uses?
A: Ylikuutio targets OpenGL version 3.1, but so far 3.0 works too,
   ie. all currently used functionality is available in OpenGL 3.0.

Q: Are there plans to support other graphics APIs?
A: Newer OpenGL versions may be supported in the future, but so far
   OpenGL 3.1 fulfils my requirements. Vulkan needs to be considered.

Q: Does Ylikuutio use modern OpenGL (VBOs)?
A: Yes, Ylikuutio uses VBOs (vertex buffer objects) and VBO indexing.

Q: Is Ylikuutio based on some other 3D engine?
A: Some parts of Ylikuutio (shaders, some file loaders, etc.) are based
on [http://www.opengl-tutorial.org/](http://www.opengl-tutorial.org/), which I really recommend for anyone
interested in learning OpenGL programming. Ylikuutio also uses external
libraries such as (in alphabetical order) Asio, GLM, GLEW, GLFW, OpenFBX,
SFML, TinyScheme, and pugixml. The rest is written from scratch.

Q: Why TinyScheme is chosen as the scripting language of Ylikuutio?
A: I like Lisp-family languages and TinyScheme fulfils my
   requirements related to a small size and a suitable license.

Q: Does Ylikuutio use right-handed or left-handed world coordinates?
A: Ylikuutio uses right-handed world coordinates, so X grows eastward, Z grows southward, and Y grow upwards.

## Implemented functionality
* 3D rendering
* 2D text
* support for different height map formats (SRTM, LAZ)
* instant rebinding of instances of classes belonging to ontological hierarchy
* callbacks
* fully functioning in-game console
* multiple scenes in the same `Universe` (`activate` console command)
* audio with Simple and Fast Multimedia Library (SFML)
* option for wireframe models (`set wireframe true`, `set wireframe false`)

## Future developments underway
* full support for different keyboard layouts in console
* custom keyboard mappings in Ajokki
* command to read console command input from file
* command to record gameplay
* command to play recorded gameplay
* running some Linux command line commands in console, with Toybox
* option to disassemble some Ylikuutio code (`Entity` objects) using NDISASM
* copy-paste in console (Shift-Ins for paste)
* console reference manual (`man` command)
* rendering to texture (for mirrors and displays)
* partially transparent 2D text
* 3D text
* partially transparent 3D text
* multiple scenes in the same `Universe` (`activate` console command)
* coordinates relative to other objects, not only to `Universe` object
* practically infinite voxel worlds (limited by `float` precision)
* collision detection between objects
* octree space partitioning
* possibility to create scenes with different spatial scales
* background loading of `Scene`s
* objects (`Species` in Ylikuutio terminology) with modifiable vertices
* making holes in objects
* splitting of objects into 2 or more pieces
* cementing of 2 or more objects into one
* morphing between objects (`Species` in Ylikuutio terminology)
* morphing between objects (`Species`) and 3D text (`Glyph`s)
* ray casting for vertex selection and vertex modifications
* vegetation created with L-system fractals
* objects with 4 or more spatial dimensions, projected to 3D space before rendering to screen
* more shaders
* sky dome
* railways
* roads
* trains, trams, and road vehicles
* more realistic static water
* flowing water
* snow and ice
* more physics
* artificial intelligence (AI) creatures
* A\* and Theta\* pathfinding
* TinyScheme as scripting language
* visual pattern recognition for AI: V1 (primary visual cortex) and V2 simulation
* GUI for scripting, asset creation etc.
* Internet gaming with ASIO

### Libraries currently in use
* The source code from [http://www.opengl-tutorial.org/](http://www.opengl-tutorial.org/) is licensed under [WTFPL Public Licence version 2](http://www.opengl-tutorial.org/download/).
* [Asio](https://think-async.com/) is licensed under [Boost software license](https://github.com/chriskohlhoff/asio/blob/master/asio/LICENSE_1_0.txt).
* [OpenGL Mathematics (GLM)](https://glm.g-truc.net/) is licensed under [The Happy Bunny License (Modified MIT License) and MIT License](http://glm.g-truc.net/copying.txt).
* [GLFW](http://www.glfw.org/) is licensed under [the zlib/libpng license](http://www.glfw.org/license.html).
* [The OpenGL Extension Wrangler Library (GLEW)](http://glew.sourceforge.net/) is licensed under [the Modified BSD License, the Mesa 3-D License (MIT) and the Khronos License (MIT)](https://github.com/nigels-com/glew#copyright-and-licensing).
* [OpenFBX](https://github.com/nem0/OpenFBX) is licensed under [the MIT license](https://github.com/nem0/OpenFBX/blob/master/LICENSE).
* [SFML](https://www.sfml-dev.org/) is licensed under [the zlib/png license](https://www.sfml-dev.org/license.php).
* [TinyScheme](http://tinyscheme.sourceforge.net/) is licensed under [BSD-style license](http://tinyscheme.sourceforge.net/license.txt).
* [pugixml](https://pugixml.org/) is licensed under [the MIT license](https://github.com/zeux/pugixml/blob/master/README.md).

### Libraries not yet in use
* [GLFM](https://github.com/brackeen/glfm) is licensed under [the zlib license](https://github.com/brackeen/glfm/blob/master/LICENSE).
* [Google logging module (glog)](https://github.com/google/glog) is licensed under [the conditions available in https://github.com/google/glog/blob/master/COPYING](https://github.com/google/glog/blob/master/COPYING).
* [FastNoiseSIMD](https://github.com/Auburns/FastNoiseSIMD) is licensed under [the MIT license](https://github.com/Auburns/FastNoiseSIMD/blob/master/LICENSE).
* [TinySpline](https://github.com/msteinbeck/tinyspline) is licensed under [the MIT license](https://github.com/msteinbeck/tinyspline/blob/master/LICENSE).

### Libraries currently not in use
* [Open Asset Import Library (assimp)](http://www.assimp.org/) is licensed under [a 3-clause BSD license](http://www.assimp.org/main_license.html).

### 3D models
* [3D model of Helsinki.](http://www.hri.fi/en/dataset/helsingin-3d-kaupunkimalli) The administrator of 3D model of Helsinki is Helsingin kaupunginkanslia and the original creator is Helsingin kaupungin kaupunginkanslia, tietotekniikka- ja viestintäosasto. The data has been downloaded from the [Helsinki Region Infoshare](http://www.hri.fi/) service 19.11.2017 using the license [Creative Commons Nimeä 4.0 Kansainvälinen (CC BY 4.0)](http://creativecommons.org/licenses/by/4.0/deed.fi).
* [Horse](https://www.blendswap.com/blends/view/76528) is made by b2przemo and it is licensed under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/). The `horse.fbx` file shipped with Ylikuutio is made from the original `horse.blend` by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* [Turbo polizei](https://www.blendswap.com/blends/view/74227) is made by corvusd and it is licensed under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/). The `turbo_polizei.fbx` file shipped with Ylikuutio is made from the original `porche_997_turbo_polizei_blendswap.blend` (sic) by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* [Rigged and animated cat](https://www.blendswap.com/blends/view/86110) is made by JonasDichelle and it is licensed under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/). The `cat.fbx` file shipped with Ylikuutio is made from the original `cat.blend` by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* Suzanne the monkey is a standard [Blender](https://www.blender.org/) object. According to Blender license information: "All your artwork – images or movie files – including the .blend files and other data files Blender can write, is free for you to use as you like." Ylikuutio does not contain any code from Blender, however. [Blender itself is released under the GNU General Public License (GPL) 2 or later](https://www.blender.org/about/license/).

### Textures
* Grass texture is from [Free Seamless Green Grass Textures](http://www.brusheezy.com/textures/20185-seamless-green-grass-textures), and is under CC-BY license.
* A Cool Seamless Orange Fur Texture is from [My Free Textures](http://www.myfreetextures.com/a-cool-seamless-orange-fur-texture/). `orange_fur_texture.bmp` is scaled down and converted into BMP from the original `ornage-fur-texture.jpg` (sic). License conditions are available on [My Free Textures License/TOU page](http://www.myfreetextures.com/sample-page/).
* Pink Marble Pavers Or Tiles Background Texture is from [My Free Textures](http://www.myfreetextures.com/marbles-pavers-tiles-background-texture/). `pavers1b2.bmp` is scaled down and converted into BMP from the original `pavers1b2.jpg`. License conditions are available on [My Free Textures License/TOU page](http://www.myfreetextures.com/sample-page/).

### Fonts
* kongtext font is made by [codeman38](http://zone38.net/), see res/fonts/kongtext/license.txt for the license.

### Map data
* [OpenStreetMap®](https://www.openstreetmap.org/) data of Helsinki, Joensuu, and other Finnish cities is open data, licensed under [the Open Data Commons Open Database License (ODbL) by the OpenStreetMap Foundation (OSMF)](https://www.openstreetmap.org/copyright). OpenStreetMap data is © OpenStreetMap contributors.
* Elevation model (2 m) of Helsinki, Joensuu, and other Finnish cities is licensed under a Creative Commons Attribution 4.0 International License (CC-BY). Contains data from [the National Land Survey of Finland Topographic Database 08/2016](http://www.maanmittauslaitos.fi/en/opendata-licence-cc40). Reference system is ETRS-TM35FIN. File format is ASCII Grid. Height system is N2000.
* [Shuttle Radar Topography Mission (SRTM)](https://www2.jpl.nasa.gov/srtm/) data around Bolivian altiplano and elsewhere in the world between 56° S and 60° N is in the public domain. SRTM is a [NASA (National Aeronautics and Space Administration)](https://www.nasa.gov/) mission. SRTM data shipped with Ylikuutio belongs to SRTMGL3 dataset. Information about different SRTM datasets is available in [OpenStreetMap Wiki](http://wiki.openstreetmap.org/wiki/SRTM).

### Audio
* [Arp Bass Loop 128 bpm.mp3](https://freesound.org/people/JPMusic82/sounds/414269/) is made by JPMusic82 and it is licensed under the [Creative Commons 0 (CC0 1.0) license](https://creativecommons.org/publicdomain/zero/1.0/).
* [Blue Play](https://freesound.org/people/Greek555/sounds/416882/) is made by Greek555 and it is licensed under the [Creative Commons 0 (CC0 1.0) license](https://creativecommons.org/publicdomain/zero/1.0/). Converted into OGG from the original `416882__greek555__blue-play.mp3`.
* [Chipland Loop (120 BPM-A Major)](https://freesound.org/people/SSS_Samples/sounds/414257/) is made by SSS\_Samples and and it is licensed under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/).
* [Dreaming Of Me](https://freesound.org/people/Greek555/sounds/419588/) is made by Greek555 and it is licensed under the [Creative Commons 0 (CC0 1.0) license](https://creativecommons.org/publicdomain/zero/1.0/). Converted into OGG from the original `419588__greek555__dreaming-of-me.mp3`.
* [Sample 97 Bpm](https://freesound.org/people/Greek555/sounds/414270/) is made by Greek555 and it is licensed under the [Creative Commons 0 (CC0 1.0) license](https://creativecommons.org/publicdomain/zero/1.0/).
* [Tecno pop base and guitar 2](https://freesound.org/people/frankum/sounds/395487/) is made by frankum and it is licensed under the [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/). Original track by Frankum & Frankumjay. Converted into OGG from the original `395487__frankum__tecno-pop-base-and-guitar-2.mp3`.


## Trademarks
* Android is a trademark of Google Inc. See [https://developer.android.com/legal.html](https://developer.android.com/legal.html).
* Coverity® and Coverity Scan® are registered trademarks of Synopsys, Inc. in the US and/or other countries. See [https://www.synopsys.com/company/legal/trademarks-brands.html](https://www.synopsys.com/company/legal/trademarks-brands.html).
* Linux® is the registered trademark of Linus Torvalds in the U.S. and other countries. See [https://www.linuxmark.org/programs/legal/trademark/attribution](https://www.linuxmark.org/programs/legal/trademark/attribution).
* Synopsys® is a registered trademark of Synopsys, Inc. in the US and/or other countries. See [https://www.synopsys.com/company/legal/trademarks-brands.html](https://www.synopsys.com/company/legal/trademarks-brands.html).
* Windows is a trademark of Microsoft. See [https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general.aspx](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general.aspx).

## Contact info
(found bugs and suggestions are very welcome!)

| variable       | value                                                         |
|:-------------- |:------------------------------------------------------------- |
| name           | Antti Nuortimo                                                |
| GitHub         | https://github.com/nrz                                        |
| Stack Overflow | https://stackoverflow.com/users/1310991/nrz                   |
| email          | antti dot nuortimo at gmail dot com                           |
|                | (please write 'ylikuutio' to email title to escape /dev/null) |

Work offers are also very welcome!
