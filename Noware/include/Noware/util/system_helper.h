#ifndef _SYSTEM_HELPER_H_
#define _SYSTEM_HELPER_H_
#include <string>
#include "Noware/util/macro_field.h"


namespace nw
{
    namespace Util
    {
        //[GLOBAL]
        //{Message send to console, in both debug/release}
        ///\param message string to send
        _GLOBAL_ void Message(std::string message);

        //[GLOBAL]
        //{Message send to console in debug build}
        ///\param debug_message string to send
        _GLOBAL_ void DebugMessage(std::string debug_message);

        //[GLOBAL]
        //{For debugging a pointer, print address}
        ///\param debug_message string to send
        ///\param address use a static_cast<void*> to convert any pointer
        _GLOBAL_ void DebugMessageP(std::string debug_message, void* address);

        //[GLOBAL]
        //{Throwing runtime error.}
        ///\param error_message string to send
        _GLOBAL_ void RuntimeError(std::string error_message);
        
        //[GLOBAL]
        //{Debug Mode only: allow console to stay open after closing}
        _GLOBAL_ void DebugExitPause();
    }
}

#endif