filter "system:windows"
    project "SDL2"
        kind "SharedLib"
        includedirs "SDL/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL/win32/lib/x64"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x64/SDL2.dll bin/Debug/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2.lib bin/Debug/"
            }

        filter "architecture:x86"
            libdirs "SDL/win32/lib/x86"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x86/SDL2.dll bin/Debug/",
                "{COPY} %{prj.name}/win32/lib/x86/SDL2.lib bin/Debug/"
            }

    project "SDL2_ttf"
        kind "SharedLib"
        includedirs "SDL_ttf/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL_ttf/win32/lib/x64"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_ttf.dll bin/Debug/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_ttf.lib bin/Debug/"
            }

        filter "architecture:x86"
            libdirs "SDL_ttf/win32/lib/x86"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x86/SDL2_ttf.dll bin/Debug/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_ttf.lib bin/Debug/"
            }

    project "SDL2_image"
        kind "SharedLib"
        includedirs "SDL_image/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL_image/win32/lib/x64"
            
            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_image.dll bin/Debug/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_image.lib bin/Debug/"
            }

        filter "architecture:x86"
            libdirs "SDL_image/win32/lib/x86"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x86/SDL2_image.dll bin/Debug/",
                "{COPY} %{prj.name}/win32/lib/x86/SDL2_image.lib bin/Debug/"
            }
