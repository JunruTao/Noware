#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "Noware/utility.h"
namespace nw
{
    class Drawable
    {
    public:
        //[Constructor]
        Drawable();
        //[Destructor] virtual
        virtual ~Drawable();

        //[Vitual MFunc]
        //{All children should override draw functions}
        // Note: Draw calles should call the global `MasterRenderer` from graphics.h/window.h
        virtual void Draw()=0;

        //[Vritual MFunc]
        //{All children should override update function}
        virtual void Update()=0;
    };
}

#endif