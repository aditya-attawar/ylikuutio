# Ylikuutio. A 3D game and simulation engine.
A hobby project of mine. Work in progress.

[![License: AGPL v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)
[![Travis CI build](https://travis-ci.org/nrz/ylikuutio.svg?branch=master)](https://travis-ci.org/nrz/ylikuutio)
[![AppVeyor build](https://ci.appveyor.com/api/projects/status/github/nrz/ylikuutio?branch=master&svg=true)](https://ci.appveyor.com/project/nrz/ylikuutio)
[![Coverity Scan](https://scan.coverity.com/projects/nrz-ylikuutio/badge.svg)](https://scan.coverity.com/projects/nrz-ylikuutio)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0d0d48dc3b6947b2ac90bebd1f3a07f2)](https://www.codacy.com/manual/antti.nuortimo/ylikuutio?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=nrz/ylikuutio&amp;utm_campaign=Badge_Grade)
[![Coverage Status](https://coveralls.io/repos/github/nrz/ylikuutio/badge.svg?branch=master)](https://coveralls.io/github/nrz/ylikuutio?branch=master)

## License
Ylikuutio is under The GNU Affero General Public License 3,
or (at your option) any later version. See COPYING file.
All my code copyright (C) 2015-2020 Antti Nuortimo.

An exception in licensing of Ylikuutio code are
Asio example source code files modified by me, which have
their original Boost Software License - Version 1.0.

Data preprocessing scripts that use Blender Python API
are not a part of Ylikuutio itself and they are under
The GNU General Public License 2 or later (at your option),
following Blender's licensing.

## Overview
Ylikuutio is a 3D game engine designed for 3D games and simulations.
Ylikuutio aims to run fast and support also older hardware.
Currently Ylikuutio works on 64-bit Linux and Windows systems.
Android support is a work in progress.
macOS and iOS will be supported in the future.
OpenGL 3.0 or newer is required.

## Ylikuutio 0.0.8 screenshots
![View of Helsinki with cats and Ylikuutio console](https://github.com/nrz/ylikuutio/blob/master/screenshots/helsinki_cats_2020-10-08.png?raw=true)
![Turbo polizei and cats](https://github.com/nrz/ylikuutio/blob/master/screenshots/turbo_polizei_2020-10-08.png?raw=true)
![Cats and debug console commands](https://github.com/nrz/ylikuutio/blob/master/screenshots/cats_2020-10-08.png?raw=true)
![Turbo polizei and debug console commands](https://github.com/nrz/ylikuutio/blob/master/screenshots/turbo_polizei_info_2020-10-08.png?raw=true)

## Articles
In [Skrolli 2018.4](https://skrolli.fi/numerot/2018-4/) there is an article
"Pelimoottori harrastusprojektina" (in Finnish, translation: "Game engine
as a hobby project"). Skrolli 2018.4 can be freely downloaded as PDF.

In [Skrolli 2019.2](https://skrolli.fi/numerot/2019-2/) there is an article
"GPGPU-laskenta" (in Finnish, translation: "GPGPU computation").
Skrolli 2019.2 can be freely downloaded as PDF.

## Compiling
Ylikuutio can be compiled with GCC, Clang or Visual Studio.
In Visual Studio compiling may break due to compiler-specific bugs.
Cross compiling from Linux® to Windows using MinGW-w64 works fine.
C++17 support is required.
CMake 2.6.2 or newer is needed for the compiling process, but
external libraries such as `glm` require CMake 3.2 or a newer version.
CMake uses git for downloading Google Test testing framework.

Ylikuutio repository in GitHub has 2 branches: `master` & `coverity_scan`.
`master` is the branch that should be up to date and it's the one to build.
`coverity_scan` is for Synopsys© Coverity Scan© analysis tool which is run
through Travis CI.

In Linux it's simple.

First, install all the necessary compilers, tools and libs. You may use
your favorite package manager such as apt, aptitude, apt-get, yum etc.
You all need these packages:
cmake make g++ gcc libx11-dev libgl1-mesa-dev libglu1-mesa-dev libsdl2-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev

Eg. with apt:

    $ sudo apt install cmake build-essential libx11-dev libgl1-mesa-dev libglu1-mesa-dev libsdl2-dev libxcursor-dev libxrandr-dev libxext-dev libxi-dev libxinerama-dev

If you are doing a cross compile from Linux to Windows, you need also:

    $ sudo apt install g++-mingw-w64 gcc-mingw-w64 binutils-mingw-w64

If you are doing a cross compile from Linux to Android™, you need also:

    $ sudo apt install android-sdk-platform-tools-common ant google-android-ndk-installer openjdk-8-jdk

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
compiling ends before you get `nirvi.exe`, `tulevaisuus.exe`,
`ajokki.exe`, `gpgpu_test.exe`, and `yli_edit.exe`.

By default compiling tests is disabled when crosscompiling from Linux
to Windows, due to this issue:
https://github.com/google/googletest/issues/606

To cross compile from Linux to Android (using Android NDK):

    $ mkdir build_android
    $ cd build_android
    $ cmake -DCMAKE_TOOLCHAIN_FILE=../android.cmake ..
    $ make

However, cross compiling from Linux to Android does not work yet!

Compiling in Visual Studio is more difficult. The recommended way to
get a binary for Windows is to cross compile from Linux to Windows.

Ylikuutio repository contains the following games/demos:

Hirvi is a first person action-adventure of the adventures of
a moose/elk called Hirvi. Cities are dangerous places for moose, and
in particular an encounter with the police may prove deadly for Hirvi,
even through moose are well-known pasifists.
"hirvi" means a moose/elk in Finnish.
Hirvi is a work in progress.

Tulevaisuus ("the future" in Finnish) is
a turn-based 3D tactical combat game with programmable robots.
The robots controlled by an evil AI have taken over the world. Almost.
The last hope of the human species is the Lisp Resistance Force.
You, as the lead Lisp hacker of the Lisp Resistance Force,
are responsible for the programming of the robots of
the Lisp Resistance Force. Your task is write Lisp
to control the robots reowned by humans.
And save the human species, too.
Tulevaisuus is a work in progress.

Ajokki is sandbox demo program to check out some properties of
Ylikuutio 3D engine. "Ajokki" is a working title named after
a Finnish bus body manufacturer.

GPGPU test is a simple GPGPU example. It computes e.g. the distances
between some railway stations on the current passenger railway network
of Finland using both floating point and unsigned short values, using
Floyd-Warshall algorithm. GPGPU test includes also some simpler examples
on how to copy data and how to shift textures. After computing,
e.g. Bash scripts `code/bash/print_float_results_of_width_32` &
`code/bash/print_integer_results_of_width_32` can be used to display
the Floyd-Warshall results in Bash.

YliEdit is a universe editor for Ylikuutio. Work in progress.

In Linux:

    $ ./hirvi
    $ ./tulevaisuus
    $ ./ajokki
    $ ./gpgpu_test
    $ ./yli_edit

In Windows:

    > hirvi.exe
    > tulevaisuus.exe
    > ajokki.exe
    > gpgpu_test.exe
    > yli_edit.exe

`hirvi.exe`, `tulevaisuus.exe`, `ajokki.exe`, `gpgpu_test.exe`, and
`yli_edit.exe` can also be executed in Linux, using Wine:

    $ wine ./hirvi.exe
    $ wine ./tulevaisuus.exe
    $ wine ./ajokki.exe
    $ wine ./gpgpu_test.exe
    $ wine ./yli_edit.exe

Press `` to get console. Press F to toggle flying on off.
Arrow keys work too. Ctrl is turbo. F1 toggles help display
and there you'll see some more options to try.

To run tests (coverage is still quite limited but underway):

    $ ./unit_tests_with_googletest

## Ylikuutio usage
This part reflects the current usage of Ylikuutio and will change as new
functionality is implemented.

At the moment, you need a `main` function (for an example, please see
`code/hirvi/hirvi.cpp` and `code/ajokki/ajokki.cpp`) which starts your
game/simulation (initialization), runs the game/simulation (the main loop)
and ends the program (cleaning-up). In all these phases mentioned above
Ylikuutio library functions may be used. Ylikuutio library code is located
in `code/ylikuutio/` tree. Ylikuutio code may change a lot and so far no
stable API has been defined. There are also some application code snippets
in `code/ylikuutio/snippets/` directory. Hirvi, Ajokki and Ylikuutio code
itself are the best references on how to use Ylikuutio in practice.

Some available console commands to try in Ajokki:
* `activate joensuu_center_and_west_scene`
* `activate helsinki_east_downtown_scene`
* `set red 1.0`
* `set green 0.15`
* `set blue 0.77`
* `print red`
* `print green`
* `print blue`
* `set x 123`
* `set y 456`
* `set z 789`
* `print x`
* `print y`
* `print z`
* `info`
* `info cat_species`
* `info cat2`
* `set wireframe true`
* `set wireframe false`
* `activate turbo_polizei_camera`
* `print turbo_polizei_bmp1.cartesian_coordinates`
* `print turbo_polizei_bmp1.x`
* `print turbo_polizei_bmp1.y`
* `print turbo_polizei_bmp1.z`
* `set turbo_polizei_bmp1.y 50`
* `set turbo_polizei_bmp1.x 100`
* `set turbo_polizei_bmp1.z 200`
* `activate cat_camera`
* `print cat1.cartesian_coordinates`
* `print cat1 x`
* `print cat1.y`
* `print cat1.z`
* `set cat1.x 123.45`
* `set cat1.z 210`
* `bind helsinki_east_downtown_orange_fur_material helsinki_east_downtown_grayscale_shader`
* `bind helsinki_east_downtown_orange_fur_material helsinki_east_downtown_shader`
* `print cat1.speed`
* `bind cat1 orient_to_south_brain`
* `bind cat1 orient_and_go_east_brain`
* `set cat1.speed 1`
* `bind cat1 orient_and_go_west_brain`
* `bind cat1 rest_brain`
* `print framebuffer_width`
* `print framebuffer_height`
* `screenshot screenshot1.data`
* `set framebuffer_width 2000`
* `set framebuffer_height 1000`
* `screenshot screenshot2.data`
* `print window_width`
* `print window_height`
* `set window_width 1000`
* `set window_height 500`
* `create-object cat_species cat3 500 100 600 3.14 0`
* `create-object cat_species cat4 500 100 650`
* `create-holobiont turbo_polizei_bmp_symbiosis polizei3 500 100 700 3.14 0`
* `create-holobiont turbo_polizei_bmp_symbiosis polizei4 480 100 700`

## FAQ
Q: What is "Ylikuutio"?
A: In Finnish, "yli" means ["over"](https://en.wiktionary.org/wiki/yli-),
   and "kuutio" means ["cube"](https://en.wiktionary.org/wiki/kuutio).
   So, "Ylikuutio" is a reference to a [hypercube](https://en.wikipedia.org/wiki/Hypercube).

Q: How is Ylikuutio software developed?
A: In [Debian GNU/Linux](https://www.debian.org/)
   ([Debian Buster](https://wiki.debian.org/DebianBuster) at the moment),
   using [Vim](https://www.vim.org/). Other tools in use include
   [Valgrind](http://valgrind.org/), [KCachegrind](https://kcachegrind.github.io/html/Home.html),
   [GDB](https://www.gnu.org/software/gdb/), [Travis CI](https://travis-ci.org/),
   and [Coverity Scan](https://scan.coverity.com/).

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
A: Ylikuutio targets OpenGL version 3.0.

Q: Are there plans to support other graphics APIs?
A: Newer OpenGL versions may be supported in the future, but so far
   OpenGL 3.0 fulfils my requirements. Vulkan needs to be considered.

Q: Does Ylikuutio use modern OpenGL (VAOs and VBOs)?
A: Yes, Ylikuutio uses VAOs (vertex array objects, VBOs (vertex buffer objects),
   and index buffers.

Q: Is Ylikuutio based on some other 3D engine?
A: Some parts of Ylikuutio (some shaders, some file loaders, etc.) are
   based on [https://www.opengl-tutorial.org/](https://www.opengl-tutorial.org/),
   which I really recommend for anyone interested in learning
   OpenGL programming. Ylikuutio also uses external libraries such as
   (in alphabetical order) Asio, Bullet, GLM, GLEW, OpenFBX, pugixml, SDL, and stb.
   The rest is written from scratch.

Q: Does Ylikuutio use right-handed or left-handed world coordinates?
A: Ylikuutio uses right-handed world coordinates,
   so X grows eastward, Z grows southward, and Y grows upwards.

Q: Is there a scripting language in Ylikuutio?
A: YliLisp scripting language is a work in progress.

## Implemented functionality
* 3D rendering
* 2D text
* support for different height map formats (SRTM, BMP)
* instant rebinding of instances of classes belonging to ontological hierarchy
* callbacks
* fully functioning in-game console
* multiple scenes in the same `Universe` (`activate` console command)
* audio with Simple DirectMedia Layer (SDL)
* option for wireframe models (`set wireframe true`, `set wireframe false`)
* GPGPU using `yli::ontology::ComputeTask` class (see also [Skrolli 2019.2](https://skrolli.fi/numerot/2019-2/) for an article in Finnish).

## Future developments underway
* full support for different keyboard layouts in console
* custom keyboard mappings
* command to read console command input from file
* command to record gameplay
* command to play recorded gameplay
* copy-paste in console (Shift-Ins for paste)
* console reference manual (`man` command)
* rendering to texture (for mirrors and displays)
* partially transparent 2D text
* 3D text
* partially transparent 3D text
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
* visual pattern recognition for AI: V1 (primary visual cortex) and V2 simulation
* GUI for scripting, asset creation etc.
* Network gaming

### Libraries currently in use
* The source code from [https://www.opengl-tutorial.org/](https://www.opengl-tutorial.org/) is licensed under [WTFPL Public Licence version 2](https://www.opengl-tutorial.org/download/).
* [Asio](https://think-async.com/) is licensed under [Boost software license](https://github.com/chriskohlhoff/asio/blob/master/asio/LICENSE_1_0.txt).
* [Bullet](http://bulletphysics.org/) is licensed under [the zlib license](https://github.com/bulletphysics/bullet3/blob/master/LICENSE.txt).
* [OpenGL Mathematics (GLM)](https://glm.g-truc.net/) is licensed under [The Happy Bunny License (Modified MIT License) and MIT License](https://glm.g-truc.net/copying.txt).
* [The OpenGL Extension Wrangler Library (GLEW)](http://glew.sourceforge.net/) is licensed under [the Modified BSD License, the Mesa 3-D License (MIT) and the Khronos License (MIT)](https://github.com/nigels-com/glew#copyright-and-licensing).
* [OpenFBX](https://github.com/nem0/OpenFBX) is licensed under [the MIT license](https://github.com/nem0/OpenFBX/blob/master/LICENSE).
* [Ryan's CMake Modules](https://github.com/rpavlik/cmake-modules) is licensed under [Boost Software License Version 1.0](https://github.com/rpavlik/cmake-modules/blob/master/LICENSE_1_0.txt).
* [SDL2](https://www.libsdl.org/) is licensed under [the zlib license](https://www.libsdl.org/).
* [stb](https://github.com/nothings/stb) is licensed under [the MIT license](https://github.com/nothings/stb/blob/master/LICENSE).
* [pugixml](https://pugixml.org/) is licensed under [the MIT license](https://github.com/zeux/pugixml/blob/master/README.md).

### Libraries not yet in use
* [Google logging module (glog)](https://github.com/google/glog) is licensed under [the conditions available in https://github.com/google/glog/blob/master/COPYING](https://github.com/google/glog/blob/master/COPYING).
* [FastNoiseSIMD](https://github.com/Auburns/FastNoiseSIMD) is licensed under [the MIT license](https://github.com/Auburns/FastNoiseSIMD/blob/master/LICENSE).
* [TinySpline](https://github.com/msteinbeck/tinyspline) is licensed under [the MIT license](https://github.com/msteinbeck/tinyspline/blob/master/LICENSE).

### 3D models
* [3D model of Helsinki.](https://www.hri.fi/en/dataset/helsingin-3d-kaupunkimalli) The administrator of 3D model of Helsinki is Helsingin kaupunginkanslia and the original creator is Helsingin kaupungin kaupunginkanslia, tietotekniikka- ja viestintäosasto. The data has been downloaded from the [Helsinki Region Infoshare](https://www.hri.fi/) service 19.11.2017 using the license [Creative Commons Nimeä 4.0 Kansainvälinen (CC BY 4.0)](https://creativecommons.org/licenses/by/4.0/deed.fi).
* [Horse](https://www.blendswap.com/blend/13903) is made by b2przemo and it is licensed under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/). The `horse.fbx` file shipped with Ylikuutio is made from the original `horse.blend` by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* [Turbo polizei](https://www.blendswap.com/blend/12758) is made by corvusd and it is licensed under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/). The `turbo_polizei.fbx` file shipped with Ylikuutio is made from the original `porche_997_turbo_polizei_blendswap.blend` (sic) by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* [Fantasy house with balcony](https://www.blendswap.com/blend/6670) is made by Daniel74 and it is licensed under [CC0 1.0 Universal (CC0 1.0) Public Domain Dedication ](https://creativecommons.org/publicdomain/zero/1.0/). The `fantasy_house_with_balcony.fbx` file shipped with Ylikuutio is made from the original `FantasyHouseNo6.blend` by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* [Freight train](https://www.blendswap.com/blend/5599) is made by SONGKRO and it is licensed under [CC0 1.0 Universal (CC0 1.0) Public Domain Dedication ](https://creativecommons.org/publicdomain/zero/1.0/). The `freight_train.fbx` file shipped with Ylikuutio is made from the original `freight.blend` by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* [Rigged and animated cat](https://www.blendswap.com/blend/18519) is made by JonasDichelle and it is licensed under [Creative Commons Attribution 3.0 Unported (CC BY 3.0) license](https://creativecommons.org/licenses/by/3.0/). The `cat.fbx` file shipped with Ylikuutio is made from the original `cat.blend` by exporting the object in [FBX](https://en.wikipedia.org/wiki/FBX) file format, using [Blender](https://www.blender.org/).
* Suzanne the monkey is a standard [Blender](https://www.blender.org/) object. According to Blender license information: "All your artwork – images or movie files – including the .blend files and other data files Blender can write, is free for you to use as you like." Ylikuutio does not contain any code from Blender, however. [Blender itself is released under the GNU General Public License (GPL) 2 or later](https://www.blender.org/about/license/).

### Textures
* Grass texture is from [Free Seamless Green Grass Textures](https://www.brusheezy.com/textures/20185-seamless-green-grass-textures), licensed under [Creative Commons Attribution (BY) License](https://support.brusheezy.com/hc/en-us/articles/360002159712-Creative-Commons-Attribution-BY-License-Definition-Usage).
* A Cool Seamless Orange Fur Texture is from [My Free Textures](http://www.myfreetextures.com/a-cool-seamless-orange-fur-texture/). `orange_fur_texture.bmp` is scaled down and converted into BMP from the original `ornage-fur-texture.jpg` (sic). License conditions are available on [My Free Textures License/TOU page](http://www.myfreetextures.com/sample-page/).
* Pink Marble Pavers Or Tiles Background Texture is from [My Free Textures](http://www.myfreetextures.com/marbles-pavers-tiles-background-texture/). `pavers1b2.bmp` is scaled down and converted into BMP from the original `pavers1b2.jpg`. License conditions are available on [My Free Textures License/TOU page](http://www.myfreetextures.com/sample-page/).

### Fonts
* kongtext font is made by [codeman38](https://zone38.net/), see res/fonts/kongtext/license.txt for the license.

### Map data
* [OpenStreetMap®](https://www.openstreetmap.org/) data of Helsinki, Joensuu, and other Finnish cities is open data, licensed under [the Open Data Commons Open Database License (ODbL) by the OpenStreetMap Foundation (OSMF)](https://www.openstreetmap.org/copyright). OpenStreetMap data is © OpenStreetMap contributors.
* Elevation model (2 m) of Helsinki, Joensuu, and other Finnish cities is licensed under a Creative Commons Attribution 4.0 International License (CC-BY). Contains data from [the National Land Survey of Finland Topographic Database 08/2016](https://www.maanmittauslaitos.fi/en/opendata-licence-cc40). Reference system is ETRS-TM35FIN. File format is ASCII Grid. Height system is N2000.
* [Shuttle Radar Topography Mission (SRTM)](https://www2.jpl.nasa.gov/srtm/) data around Bolivian altiplano, Tallinn and elsewhere in the world between 56° S and 60° N is in the public domain. SRTM is a [NASA (National Aeronautics and Space Administration)](https://www.nasa.gov/) mission. SRTM data shipped with Ylikuutio belongs to SRTMGL3 dataset. Information about different SRTM datasets is available in [OpenStreetMap Wiki](https://wiki.openstreetmap.org/wiki/SRTM).

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

## Contributions and bugfixes
* Antti Nuortimo (most of Ylikuutio code)
* Mikko Rasa (bugfixes)

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
