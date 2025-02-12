#pragma once

#include <vector>
#include <glm/vec4.hpp>

#include "CTextureCache.h"
#include "WallpaperEngine/Application/CWallpaperApplication.h"
#include "WallpaperEngine/Input/CInputContext.h"
#include "WallpaperEngine/Input/CMouseInput.h"
#include "WallpaperEngine/Render/Drivers/CVideoDriver.h"
#include "WallpaperEngine/Render/Drivers/Output/COutput.h"
#include "WallpaperEngine/Render/Drivers/Output/COutputViewport.h"

namespace WallpaperEngine
{
    namespace Application
    {
        class CWallpaperApplication;
    }

    namespace Render
    {
        namespace Drivers
        {
            class CVideoDriver;

            namespace Output
            {
                class COutput;
                class COutputViewport;
            }
        }

        class CWallpaper;
        class CTextureCache;

        class CRenderContext
        {
        public:
            CRenderContext (Drivers::CVideoDriver& driver, Input::CInputContext& input, CWallpaperApplication& app);

            void render (Drivers::Output::COutputViewport* viewport);
            void setDefaultWallpaper (CWallpaper* wallpaper);
            void setWallpaper (const std::string& display, CWallpaper* wallpaper);
            [[nodiscard]] Input::CInputContext& getInputContext () const;
            [[nodiscard]] const CWallpaperApplication& getApp () const;
            [[nodiscard]] const Drivers::CVideoDriver& getDriver () const;
            [[nodiscard]] const Drivers::Output::COutput& getOutput () const;
            const ITexture* resolveTexture (const std::string& name);

        private:
            /** Video driver in use */
            Drivers::CVideoDriver& m_driver;
            /** Maps screen -> wallpaper list */
            std::map <std::string, CWallpaper*> m_wallpapers;
            /** Default wallpaper to use */
            CWallpaper* m_defaultWallpaper;
            /** Input context for interactions */
            Input::CInputContext& m_input;
            /** App that holds the render context */
            CWallpaperApplication& m_app;
            /** Texture cache for the render */
            CTextureCache* m_textureCache;
        };
    }
}