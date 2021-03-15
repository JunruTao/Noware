#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "Noware/utility.h"

namespace nw
{
    namespace Window
    {
        class Renderer
        {
        public:
            Renderer(std::string window_name);
            ~Renderer();
            void Resize(hEvent h_event);
            hRenderer GetHandle();
        private:
            hRenderer _hrenderer;
        };
    }
}
#endif