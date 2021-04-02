#include "Noware/util/system_helper.h"
#include <stdexcept>
#include <iostream>

// [SYSTEM HELPER] Force Send Message
void nw::Util::Message(std::string message)
{
    std::cout << message << std::endl;
}

// [SYSTEM HELPER] Message in Debug mode
void nw::Util::DebugMessage(std::string debug_message)
{
#ifdef DEBUG
    nw::Util::Message(debug_message);
#endif
}

// [SYSTEM HELPER] Debug a pointer (Print adress and some information)
void nw::Util::DebugMessageP(std::string debug_message, void *address)
{
#ifdef DEBUG
    std::cout << ">>>> " << debug_message << " at address: [ "
              << address << " ]" << std::endl;
#endif
}

// [SYSTEM HELPER] Runtime Error Sender
void nw::Util::RuntimeError(std::string error_message)
{
    nw::Util::Message(error_message);
    throw std::runtime_error(error_message);
}


// [SYSTEM HELPER] Exit Pausing
void nw::Util::DebugExitPause()
{
#ifdef DEBUG
    std::cout<< "\n\n[Noware::Util] Press Any Key to exit...\n";
    std::cin.ignore();
#endif
}

void nw::Util::DebugCaller(std::string caller_name)
{
#ifdef DEBUG
    std::cout<<"["<<caller_name<<"] has called"<<std::endl;
#endif
}

void nw::Util::DebugCallerConstructor(std::string object_name)
{
#ifdef DEBUG
    std::cout<<"["<<object_name<<"'s Constructor] has called"<<std::endl;
#endif   
}

void nw::Util::DebugCallerDestructor(std::string object_name)
{
#ifdef DEBUG
    std::cout<<"["<<object_name<<"'s Destructor] has called"<<std::endl;
#endif   
}