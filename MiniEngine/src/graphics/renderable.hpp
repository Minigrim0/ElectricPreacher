#pragma once

#include "core/core.hpp"

namespace MiniEngine {
namespace Graphics {
class ME_API Renderable {
    virtual void OnRender() = 0;
    virtual void OnUpdate() = 0;
};
} // namespace Graphics
} // namespace MiniEngine
