#include "CWaylandFullScreenDetector.h"

using namespace WallpaperEngine::Render::Drivers::Detectors;

CWaylandFullScreenDetector::CWaylandFullScreenDetector (Application::CApplicationContext& appContext, CWaylandOpenGLDriver& driver) :
    CFullScreenDetector (appContext)
{
}

CWaylandFullScreenDetector::~CWaylandFullScreenDetector () {
    ;
}

bool CWaylandFullScreenDetector::anythingFullscreen () const {
    return false; // todo
}

void CWaylandFullScreenDetector::reset () {
    ;
}