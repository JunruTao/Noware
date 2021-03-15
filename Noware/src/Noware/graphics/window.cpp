#include "Noware/graphics/window.h"

//[Constructor]
nw::Window::Renderer::Renderer(std::string window_name)
{
    // Renderer Settings
    sf::ContextSettings sf_setting;
    sf_setting.antialiasingLevel = 8;

    //Create Window:
    _hrenderer = new sf::RenderWindow(
        sf::VideoMode(nw::Config::WINDOW_SIZE_INIT_X,
                      nw::Config::WINDOW_SIZE_INIT_Y),
        sf::String(window_name),
        sf::Style::Default,
        sf_setting);

    
    //Test on window Creation
    if(!_hrenderer)
    {
        // Window is not created:
        nw::Util::RuntimeError(
            "[nw::Window::Renderer - Constructor] Failed to create window."
            );
    }
    else
    {
        // Window handle is successfully registed
        ____HERE_HAS_DEBUG_FUNCTION____
        nw::Util::DebugMessage("[nw::Window::Renderer] - Register status: [ SUCCESS ]");
        nw::Util::DebugMessageP("- Window Renderer Registry",static_cast<void*>(_hrenderer));
    }

    // Create viewport set into window
    sf::View view(sf::FloatRect(0, 0,
                                (float)nw::Config::WINDOW_SIZE_INIT_X,
                                (float)nw::Config::WINDOW_SIZE_INIT_Y));
    _hrenderer->setView(view);
    _hrenderer->setFramerateLimit(nw::Config::WINDOW_VAR_FRAMELIMIT); //TODO: Set Frame limit from configuration
    _hrenderer->setVerticalSyncEnabled(true);
}

//[Destructor]
nw::Window::Renderer::~Renderer()
{
    nw::Util::DebugMessage("[nw::Window::Renderer] - Delete Window Handle");
    nw::Util::DebugMessageP("- Delete Renderer Window Handle",static_cast<void*>(_hrenderer));
    delete _hrenderer;
}

//[Window Resize -> In Refresh Loop]
void nw::Window::Renderer::Resize(hEvent h_event)
{
    //TODO: Use the reference from Editor TD
}

nw::hRenderer nw::Window::Renderer::GetHandle()
{
    return this->_hrenderer;
}