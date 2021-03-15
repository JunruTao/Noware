#ifndef _UTILITY_H_
#define _UTILITY_H_

// [ INCLUDE FIELD ] Linking external libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

//  [ INCLUDE FIELD ] Including internal Utility definitions
#include "Noware/util/configure.h"
#include "Noware/util/system_helper.h"


namespace nw
{
    // passing 
    //
    // Warping Basic SFML types
    typedef sf::RenderWindow* hRenderer;
    typedef sf::Event* hEvent;
    namespace Util
    {
        extern void Test();
    }
}

#endif