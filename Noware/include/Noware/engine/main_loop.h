#ifndef _MAIN_LOOP_
#define _MAIN_LOOP_
#include "Noware/graphics.h"

namespace nw
{
    //[GLOBAL]
    //{Hide from user, the actual while loop and event pulling}
    _GLOBAL_ void ProgramLoop();
    
    //[Namespace]
    //{Important: Game registration namespace}
    // all functions under this namespace should be defined in game.cpp or external
    // user scripts.
    namespace GR
    {
        //[GLOBAL]
        //{User should define this function}
        // in this field, user should create a Renderer and move it into the RenderPool.
        _GLOBAL_ void InitPlayground();
        _GLOBAL_ void ProcessEvent();
        _GLOBAL_ void DrawCalls();
    }




    namespace GeoPool
    {
        //[GLOBAL VAR]
        // data pool stores all the custom SFML drawables
        _GLOBAL_ std::vector<std::unique_ptr<sf::Drawable>> SFML;
    }

    //[GLOBAL]
    //{This function all you to add custom sfml drables to draw} 
    // Do remember this function is more or less a debug/testing function. Use Noware 
    // geometry or types instead of this one;
    ////\param uptr_sfDrawable  unique_ptr of sf::Drawable, make them smart pointers.
    _GLOBAL_ void PushSfmlGeo(std::unique_ptr<sf::Drawable>& uptr_sfDrawable);

    //[GLOBAL]
    //{Drawing all the temporal sfml geos. Call this function in DrawCalls()}
    _GLOBAL_ void DrawSfmlGeo();
}

#endif