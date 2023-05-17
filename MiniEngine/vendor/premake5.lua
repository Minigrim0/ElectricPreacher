filter "system:windows"
    project "SDL"
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

        filter {"system:linux", "action:gmake" }
            kind "SharedLib"
            language "C"
            buildoptions { "-lSDL_ttf" }

    project "SDL_image"
        filter "system:windows"
            kind "SharedLib"
            language "C"
            includedirs "SDL_image/win32/include"

            filter "architecture:x86_64"
                libdirs "SDL_image/win32/lib/x64"
            filter "architecture:x86"
                libdirs "SDL_image/win32/lib/x86"

project "tinyxml2"
    location "%{prj.name}"
    kind "SharedLib"
    language "C++"
    includedirs "tinyxml2/include"
    files "tinyxml2/src/tinyxml2.cpp"

    targetdir ("bin/%{prj.name}")
    objdir (".obj/%{prj.name}")
