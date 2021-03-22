#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <memory>
#include "Noware/utility.h"

namespace nw
{
    namespace Window
    {
        // [CLASS]
        //{Renderer Window Class, warping the sf::RenderWindow}
        class Renderer
        {
        public:
            //[Constructor]
            ////\param window_name the text of the window title
            Renderer(std::string window_name);
            //[Destructor]
            ~Renderer();
            
            // **Public Functions**
            
            //[CLASS PUB]
            //{This function should be called in the event loop, handling the window resize}
            ////\param h_event event handle(pointer)
            void Resize(hEvent h_event);

            //[CLASS PUB]
            //{Getter: getting the pointer of the renderer}
            hRenderer GetHandle();
        private:
            // **Private Functions**
            
            //[CLASS PRIV]
            //{Private: get evaluated the sfml window style emum}
            /////\return window style enum (sf::Style)
            unsigned int _evalWindowStyle();
            
            // **Private Parameters**

            //[PRIV MEMBER]
            // resource: sfml RenderWindow pointer
            hRenderer _hrenderer;
        };

        //[GOBAL VAR]
        // The Master window
        _GLOBAL_ Renderer* MasterRenderer;

        //[GLOBAL]
        //{Use this function to register the main window and its creation}
        // .
        // PLEASE CALL THIS FUNCTION IN @InitPlayground()
        ////\param name the string name of the window title
        _GLOBAL_ void MasterRegister(std::string name);

        // *-------Window Global Utility Functions------*

        //[GLOBAL]
        // {Override the initial window size of the next created window}
        ////\param init_width    the width of the next created window
        ////\param init_height   the height of the next created window
        _GLOBAL_ void setInitSize(unsigned int init_width, unsigned int init_height);

        //[GLOBAL]
        // {Override the minimum window size of the next created window}
        ////\param init_width    the width of the next created window
        ////\param init_height   the height of the next created window
        _GLOBAL_ void setMinSize(unsigned int min_width, unsigned int min_height);

        //[GLOBAL]
        // {Override default mode : Fullscreen}
        ////\param if_fullscreen true/false
        _GLOBAL_ void setFullScreen(bool if_fullscreen);

        //[GLOBAL]
        // {Override default mode: Resizable}
        ////\param if_resizable true/false
        _GLOBAL_ void setResizable(bool if_resizable);
        
        //[GLOBAL_VAR]
        // {if enter fullscreen? (next window)}
        _GLOBAL_ bool MODE_FULLSCREEN; 
        
        //[GLOBAL VAR]
        // {if resizable (next window)}
        _GLOBAL_ bool MODE_RESIZABLE;
    }
}
#endif