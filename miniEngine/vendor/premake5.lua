project "SDL"
    filter "system:windows"
        kind "StaticLib"
        language "C"
        includedirs "SDL/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL/win32/lib/x64"
        filter "architecture:x86"
            libdirs "SDL/win32/lib/x86"

project "SDL_ttf"
    filter "system:windows"
        kind "StaticLib"
        language "C"
        includedirs "SDL_ttf/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL_ttf/win32/lib/x64"
        filter "architecture:x86"
            libdirs "SDL_ttf/win32/lib/x86"

project "SDL_image"
    filter "system:windows"
        kind "StaticLib"
        language "C"
        includedirs "SDL_image/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL_image/win32/lib/x64"
        filter "architecture:x86"
            libdirs "SDL_image/win32/lib/x86"
