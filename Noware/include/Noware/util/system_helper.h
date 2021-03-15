#ifndef _SYSTEM_HELPER_H_
#define _SYSTEM_HELPER_H_
#include <string>

// [Code Helper] Notation macros, has no specific meaning
#define ____HERE_HAS_DEBUG_FUNCTION____
#define ____INPUT____

namespace nw
{
    namespace Util
    {
        extern void Message(std::string message);
        extern void DebugMessage(std::string debug_message);
        extern void DebugMessageP(std::string debug_message, void* address);
        extern void RuntimeError(std::string error_message);
    }
}

#endif