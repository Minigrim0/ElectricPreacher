#pragma once

#include "core/core.hpp"

namespace MiniEngine::Graphics {
/**
 * @brief A renderable object that must implement OnRender & OnUpdate
 */
class ME_API Renderable {
    virtual void OnRender() = 0;
    virtual void OnUpdate() = 0;
};
} // namespace MiniEngine::Graphics
