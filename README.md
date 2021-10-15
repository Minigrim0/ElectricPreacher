# ElectricPreacher

A c++ written open-source role-play game

![Linux Build](https://github.com/Minigrim0/ElectricPreacher/actions/workflows/linux_build.yml/badge.svg) 
![Windows Build](https://github.com/Minigrim0/ElectricPreacher/actions/workflows/windows_build.yml/badge.svg)

## Dependencies

### SDL2

#### Using APT
```
sudo apt update
sudo apt install libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev
```

#### Using pacman
```
sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

# Compilation

## Linux

```bash
# From repository's root
cd build
cmake ..
make
```

To launch the game then :
```
cp ../assets/ ./ -r
./ElectricPreacher
```

## Windows (Not working for now)
Using MSYS2 :

```bash
# Install required packages
pacman -Syu
pacman -S mingw-w64-x86_64-toolchain
pacman -S make cmake
pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_mixer

#external lib
pacman -S mingw-w64-x86_64-nlohmann-json

# Build the executable
make all
```

### 3rd party libraries

* [JSON for Modern C++](https://github.com/nlohmann/json)

  `Lohmann, N. JSON for Modern C++ (Version 3.10.0) [Computer software]. https://github.com/nlohmann`

* [Tiny XML II](https://github.com/leethomason/tinyxml2)
