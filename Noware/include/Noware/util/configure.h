#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_
#include "Noware/util/macro_field.h"

//[ Config - Global Variables ]
namespace nw
{
    namespace Config
    {
        // =============================================== //
        // -----------[Config] Window Properties---------- //
        
        //[GLOBAL VAR]
        //{window: set the maximum framerate i.g."30.0FPS"}
        // Note: The frame limit will be global, will no be varies.
        extern float WINDOW_VAR_FRAMELIMIT;
        
        //[GLOBAL VAR]
        //{window: Render Window's intial width}
        extern unsigned int WINDOW_SIZE_INIT_X;

        //[GLOBAL VAR]
        //{window: Render Window's intial height}
        extern unsigned int WINDOW_SIZE_INIT_Y;
        
        //[GLOBAL VAR]
        //{window: Render Window's runtime minimum width}
        extern unsigned int WINDOW_SIZE_MIN_X;
        
        //[GLOBAL VAR]
        //{window: Render Window's runtime maxinum height}
        extern unsigned int WINDOW_SIZE_MIN_Y;
        
    }
}

#endif