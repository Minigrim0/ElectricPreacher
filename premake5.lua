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
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/tinyxml2/src/tinyxml2.cpp",
    }

    includedirs {
        "%{prj.name}/src/",
        "%{IncludeDir.tinyxml2}",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.SDL2_image}",
        "%{IncludeDir.SDL2_ttf}",
        "%{IncludeDir.JSON}",
        "%{IncludeDir.spdlog}"
    }

    links {
        "SDL2",
        "SDL2_image",
        "SDL2_ttf",
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
            "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/ElectricPreacher",
            "{COPY} vendor/bin/Debug/SDL2.dll ../bin/" .. outputdir .. "/ElectricPreacher",
            "{COPY} vendor/bin/Debug/SDL2_image.dll ../bin/" .. outputdir .. "/ElectricPreacher",
            "{COPY} vendor/bin/Debug/SDL2_ttf.dll ../bin/" .. outputdir .. "/ElectricPreacher"
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

    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MDd"

project "ElectricPreacher"
    location "ElectricPreacher"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        -- "%{prj.name}/src/**.hpp",
        -- "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/main.cpp",
    }

    includedirs
    {
        "%{prj.name}/src/",
        "MiniEngine/src",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.SDL2_image}",
        "%{IncludeDir.SDL2_ttf}",
        "%{IncludeDir.JSON}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.tinyxml2}"
    }

    filter "system:windows"
        links
        {
            "SDL2",
            "SDL2main",
            "MiniEngine"
        }

        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines {
            "ME_PLATFORM_WINDOWS",
        }
        
        filter { "configurations:Release" }
            buildoptions "/MT"

        filter {  "configurations:Debug" }
            buildoptions "/MDd"

    filter "system:linux"
            links
            {
                "MiniEngine",
                "SDL2",
                "SDL2_image",
                "SDL2_ttf",
                "dl",
                "pthread"
            }
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
