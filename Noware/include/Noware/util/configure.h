#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_


//[ Config - Global Variables ]
namespace nw
{
    namespace Config
    {
        //===============================================//
        //-----------[Config] Window Properties----------//
        //
        //[window] Render Window's intial width
        extern unsigned int WINDOW_SIZE_INIT_X;
        //[window] Render Window's intial height
        extern unsigned int WINDOW_SIZE_INIT_Y;
        //
        //[window] Render Window's runtime minimum width
        extern unsigned int WINDOW_SIZE_MIN_X;
        //[window] Render Window's runtime maxinum height
        extern unsigned int WINDOW_SIZE_MIN_Y;
        //
        //[window] When reize, if the viewport stretched or extended
        extern bool WINDOW_IF_STRETCHABLE;
        //[window] if allowing uses to resize the window
        extern bool WINDOW_IF_RESIZABLE;
        extern bool WINDOW_IF_BORDERLESS;
        extern bool WINDOW_IF_FULLSCREEN;
        //TODO here, window style settings and mechanisms
        //
        //[window] set the maximum framerate i.g."30.0FPS"
        extern float WINDOW_VAR_FRAMELIMIT;
    }
}

#endif