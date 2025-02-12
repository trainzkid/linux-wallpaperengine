#pragma once

#include "COutputViewport.h"

namespace WallpaperEngine::Render::Drivers::Output
{
    class CX11OutputViewport : public COutputViewport
    {
    public:
        CX11OutputViewport (glm::ivec4 viewport, std::string name);

        void makeCurrent () override;
        void swapOutput () override;
    };
}
