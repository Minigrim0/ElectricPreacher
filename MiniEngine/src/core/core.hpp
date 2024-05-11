#pragma once

/**
 * @brief everything related to the game engine rather than the game itself will be found in this
 * namespace
 */
namespace MiniEngine {}

#ifdef ME_PLATFORM_WINDOWS
#ifdef ME_BUILD_DLL
#define ME_API __declspec(dllexport)
#else
#define ME_API __declspec(dllimport)
#endif
#else
#define ME_API
#endif
