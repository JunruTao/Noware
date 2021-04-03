#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "Noware/util/externals.h"

//  [ INCLUDE FIELD ] Including internal Utility definitions
#include "Noware/util/configure.h"
#include "Noware/util/system_helper.h"
#include "Noware/util/math.h"
#include "Noware/util/io_font_manager.h"
#include "Noware/util/io_image_manager.h"


namespace nw
{
    // passing 
    
    //[Typedefs]
    // Warping Basic SFML types

    typedef sf::RenderWindow* hRenderer;
    typedef sf::Event* hEvent;
    
    namespace Util
    {
        extern void Test();
    }
}

#endif