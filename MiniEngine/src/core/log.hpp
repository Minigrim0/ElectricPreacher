#pragma once

#include <memory>

#include "core.hpp"
#include "spdlog/spdlog.h"

namespace MiniEngine {
    class ME_API Log {
    public:
        static void init();
        inline static std::shared_ptr<spdlog::logger> &get_core_logger() { return s_core_logger; }
        inline static std::shared_ptr<spdlog::logger> &get_client_logger() { return s_client_logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_core_logger;
        static std::shared_ptr<spdlog::logger> s_client_logger;
    };
}

// Core log macros
#define ME_CORE_TRACE(...)    ::MiniEngine::Log::get_core_logger()->trace(__VA_ARGS__)
#define ME_CORE_INFO(...)     ::MiniEngine::Log::get_core_logger()->info(__VA_ARGS__)
#define ME_CORE_WARN(...)     ::MiniEngine::Log::get_core_logger()->warn(__VA_ARGS__)
#define ME_CORE_ERROR(...)    ::MiniEngine::Log::get_core_logger()->error(__VA_ARGS__)
#define ME_CORE_FATAL(...)    ::MiniEngine::Log::get_core_logger()->fatal(__VA_ARGS__)

// Client log macros
#define ME_TRACE(...)	      ::MiniEngine::Log::get_client_logger()->trace(__VA_ARGS__)
#define ME_INFO(...)	      ::MiniEngine::Log::get_client_logger()->info(__VA_ARGS__)
#define ME_WARN(...)	      ::MiniEngine::Log::get_client_logger()->warn(__VA_ARGS__)
#define ME_ERROR(...)	      ::MiniEngine::Log::get_client_logger()->error(__VA_ARGS__)
#define ME_FATAL(...)	      ::MiniEngine::Log::get_client_logger()->fatal(__VA_ARGS__)