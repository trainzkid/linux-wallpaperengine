#pragma once

#include "WallpaperEngine/Application/CApplicationContext.h"

namespace WallpaperEngine::Render::Drivers::Detectors
{
    class CFullScreenDetector
    {
    public:
        CFullScreenDetector (Application::CApplicationContext& appContext);

        /**
         * @return If anything is fullscreen
         */
        [[nodiscard]] virtual bool anythingFullscreen () const = 0;

        /**
         * Restarts the fullscreen detector, specially useful if there's any resources tied to the output driver
         */
        virtual void reset () = 0;
        /**
         * @return The application context using this detector
         */
        [[nodiscard]] Application::CApplicationContext& getApplicationContext () const;

    private:
        Application::CApplicationContext& m_applicationContext;
    };
}