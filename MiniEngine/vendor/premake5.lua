filter "system:windows"
    project "SDL2"
        kind "SharedLib"
        includedirs "SDL2/win32/include"

        filter "architecture:x86_64"
            libdirs {
                "SDL2/win32/lib/x64/"
            }

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x64/SDL2.dll bin/%{cfg.buildcfg}/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2.lib bin/%{cfg.buildcfg}/"
            }

        filter "architecture:x86"
            libdirs {
                "SDL2/win32/lib/x86/"
            }

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x86/SDL2.dll bin/%{cfg.buildcfg}/",
                "{COPY} %{prj.name}/win32/lib/x86/SDL2.lib bin/%{cfg.buildcfg}/"
            }

    project "SDL2main"
        kind "StaticLib"
        includedirs "SDL2/win32/include"

        filter "architecture:x86_64"
            libdirs {
                "SDL2/win32/lib/x64/"
            }

            postbuildcommands {
                "{COPY} SDL2/win32/lib/x64/SDL2main.lib bin/%{cfg.buildcfg}/",
            }

        filter "architecture:x86"
            libdirs {
                "SDL2/win32/lib/x86/"
            }

            postbuildcommands {
                "{COPY} SDL2/win32/lib/x86/SDL2main.lib bin/%{cfg.buildcfg}/",
            }

    project "SDL2_ttf"
        kind "SharedLib"
        includedirs "SDL2_ttf/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL2_ttf/win32/lib/x64/"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_ttf.dll bin/%{cfg.buildcfg}/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_ttf.lib bin/%{cfg.buildcfg}/"
            }

        filter "architecture:x86"
            libdirs "SDL2_ttf/win32/lib/x86/"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x86/SDL2_ttf.dll bin/%{cfg.buildcfg}/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_ttf.lib bin/%{cfg.buildcfg}/"
            }

    project "SDL2_image"
        kind "SharedLib"
        includedirs "SDL2_image/win32/include"

        filter "architecture:x86_64"
            libdirs "SDL2_image/win32/lib/x64/"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_image.dll bin/%{cfg.buildcfg}/",
                "{COPY} %{prj.name}/win32/lib/x64/SDL2_image.lib bin/%{cfg.buildcfg}/"
            }

        filter "architecture:x86"
            libdirs "SDL2_image/win32/lib/x86/"

            postbuildcommands {
                "{COPY} %{prj.name}/win32/lib/x86/SDL2_image.dll bin/%{cfg.buildcfg}/",
                "{COPY} %{prj.name}/win32/lib/x86/SDL2_image.lib bin/%{cfg.buildcfg}/"
            }
