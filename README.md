# ElectricPreacher

A c++ written open-source role-play game

![Linux Build](https://github.com/Minigrim0/ElectricPreacher/actions/workflows/linux_build.yml/badge.svg) 
![Windows Build](https://github.com/Minigrim0/ElectricPreacher/actions/workflows/windows_build.yml/badge.svg)

## Dependencies

### Linux

* APT
```
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

* Pacman
```
sudo pacman -S sdl2 sdl2_image sdl2_ttf
```

# Compilation

## Linux

```bash
premake5 gmake2
make config={release|debug}
```

To launch the game then :
```
cp ../assets/ ./ -r
./ElectricPreacher
```

## Windows
```
.\vendor\premake\premake5.exe vs2022
```

Then open the solution in Visual Studio and build it.

### 3rd party libraries

* [JSON for Modern C++](https://github.com/nlohmann/json)

  `Lohmann, N. JSON for Modern C++ (Version 3.10.0) [Computer software]. https://github.com/nlohmann`

* [Tiny XML 2](https://github.com/leethomason/tinyxml2)
