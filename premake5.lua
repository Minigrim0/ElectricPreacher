workspace "ElectricPreacher"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL2"] = "MiniEngine/vendor/SDL2/win32/include"
IncludeDir["SDL2_image"] = "MiniEngine/vendor/SDL2_image/win32/include"
IncludeDir["SDL2_ttf"] = "MiniEngine/vendor/SDL2_ttf/win32/include"
IncludeDir["JSON"] = "MiniEngine/vendor/json/include"
IncludeDir["spdlog"] = "MiniEngine/vendor/spdlog/include"
IncludeDir["tinyxml2"] = "MiniEngine/vendor/tinyxml2/include"

Linux_SDL_build_options = {}
Linux_SDL_build_options["SDL"] = "`sdl2-config --cflags --libs`"
Linux_SDL_build_options["SDL_image"] = "-lSDL2_image"
Linux_SDL_build_options["SDL_ttf"] = "-lSDL2_ttf"

include "MiniEngine/vendor/"

project "MiniEngine"
    location "MiniEngine"
    kind "SharedLib"
    language "c++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir (".obj/" .. outputdir .. "/%{prj.name}")

    links {
        "SDL2",
        "SDL2_image",
        "SDL2_ttf",
        "tinyxml2"
    }

    files {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src/",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.SDL2_image}",
        "%{IncludeDir.SDL2_ttf}",
        "%{IncludeDir.JSON}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.tinyxml2}"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "ME_PLATFORM_WINDOWS",
            "ME_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/ElectricPreacher")
        }

    filter "system:linux"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        linkoptions {
            "%{Linux_SDL_build_options.SDL2}",
            "%{Linux_SDL_build_options.SDL2_image}",
            "%{Linux_SDL_build_options.SDL2_ttf}"
        }

        defines {
            "ME_PLATFORM_LINUX"
        }

    filter "configurations:Debug"
        defines "ME_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ME_RELEASE"
        optimize "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"


project "ElectricPreacher"
    location "ElectricPreacher"
    kind "ConsoleApp"
    language "c++"

    targetdir "bin/%{cfg.buildcfg}"
    objdir ".obj/%{cfg.buildcfg}"

    files {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src/",
        "MiniEngine/src",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.SDL_image}",
        "%{IncludeDir.SDL_ttf}",
        "%{IncludeDir.JSON}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.tinyxml2}"
    }

    links {
        "MiniEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "ME_PLATFORM_WINDOWS",
            "ME_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/ElectricPreacher")
        }

    filter "system:linux"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        linkoptions {
            "%{Linux_SDL_build_options.SDL}",
            "%{Linux_SDL_build_options.SDL_image}",
            "%{Linux_SDL_build_options.SDL_ttf}"
        }

        defines {
            "ME_PLATFORM_LINUX",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"