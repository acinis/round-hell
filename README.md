# RoundHell

## About game

Simple bullet hell game with round game world.

## About code

> Wanderer - who enters this land - be aware of mistakes, bad approaches, dead-ends, reinventing the wheel, and reworking some unimportant corner over and over again.
> There will be dragons... Or at least some winged creepy snakes around.
> You have been warned, so... Welcome!
>
> *\[Text engraved on a boulder - at safe edge of grim old forest - where you are standing now.\]*

# History and roadmap

* [x] v0.1.x - First attempt, abandoned.
* [ ] v0.2.x - Gluing old pieces together.
* [ ] ...
* [ ] v0.3.0 - (Almost) All tests and documentation done. Cleaned-up code.
* [ ] ...
* [ ] v1.0.0 - Working game.

# Building and running

*Not so user friendly unfortunately. Currently you must install a bunch of libraries or edit `extern/CMakeLists.txt` so SDL and SDL_ttf will download and build own dependencies automatically.*

* Install *SDL* dependencies listed [here](https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md#build-dependencies).
* Install development packages of following libraries:
  * *FreeType*
  * *HarfBuzz*
  * *PlutoSVG*
  * *PlutoVG*
* Ensure you have recent *GCC* with C++23 support (tested on 16.2) and *CMake* (at least 3.29). *Clang* (and probably *MSVC*) should also work.

Next steps are rather standard:

```shell
# `--recurse-submodules` option requires Git 2.13 or later.
git clone --recurse-submodules https://github.com/acinis/round-hell.git
cd round-hell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
# Executable must be run from its own directory.
cd bin/Release/
./round-hell
```

# Used libraries

* [SDL3](https://github.com/libsdl-org/SDL)
  * [SDL3_image](https://github.com/libsdl-org/SDL_image)
  * [SDL3_mixer](https://github.com/libsdl-org/SDL_mixer)
  * [SDL3_ttf](https://github.com/libsdl-org/SDL_ttf)
* [EnTT](https://github.com/skypjack/entt)
* [GLM](https://github.com/g-truc/glm)

# License

Code released under the [**MIT license**](/LICENSE.txt).

