workspace "ElectricPreacher"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL2"] = "MiniEngine/vendor/SDL/win32/include"
IncludeDir["SDL_image"] = "MiniEngine/vendor/SDL_image/win32/include"
IncludeDir["SDL_ttf"] = "MiniEngine/vendor/SDL_ttf/win32/include"
IncludeDir["JSON"] = "MiniEngine/vendor/json/include"
IncludeDir["spdlog"] = "MiniEngine/vendor/spdlog/include"

include "MiniEngine/vendor/"

project "MiniEngine"
    location "MiniEngine"
    kind "SharedLib"
    language "c++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir (".obj/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/includes/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src/",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.SDL_image}",
        "%{IncludeDir.SDL_ttf}",
        "%{IncludeDir.JSON}",
        "%{IncludeDir.spdlog}"
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

        defines {
            "ME_PLATFORM_LINUX",
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
        "%{prj.name}/src/includes/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "MiniEngine/src/includes",
        "MiniEngine/vendor/spdlog/include"
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

        defines {
            "ME_PLATFORM_LINUX",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"