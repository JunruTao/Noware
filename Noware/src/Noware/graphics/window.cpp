#include "Noware/graphics/window.h"
#include "math.h"

// [-------Window Global Utility Functions------]
// .
// .
//[Window Size] Overriding the global vars: Init Size
void nw::Window::setInitSize(unsigned int init_width, unsigned int init_height)
{
    nw::Config::WINDOW_SIZE_INIT_X = init_width;
    nw::Config::WINDOW_SIZE_INIT_Y = init_height;
}

//[Window Size] Overriding the global vars: Mininum Size
void nw::Window::setMinSize(unsigned int min_width, unsigned int min_height)
{
    nw::Config::WINDOW_SIZE_MIN_X = min_width;
    nw::Config::WINDOW_SIZE_MIN_Y = min_height;
}
// .
// [Window:: Global Vars]
bool nw::Window::MODE_FULLSCREEN = false;
bool nw::Window::MODE_RESIZABLE = true;

//[Window Mode] Overriding: fullscreen
void nw::Window::setFullScreen(bool if_fullscreen)
{
    nw::Window::MODE_FULLSCREEN = if_fullscreen;
}

//[Window Mode] Overriding: resizable
void nw::Window::setResizable(bool if_resizable)
{
    nw::Window::MODE_RESIZABLE = if_resizable;
}








//[Private: get window style]: returning a sf::Style int
unsigned int nw::Window::Renderer::_evalWindowStyle()
{
    if(nw::Window::MODE_FULLSCREEN)
    {
        nw::Util::DebugMessage("[Window Style] = FullScreen");
        return sf::Style::Fullscreen;
    }
    else
    {
        nw::Util::DebugMessage("[Window Style] = Default");
        return sf::Style::Default;
    }
}


//[Constructor]
nw::Window::Renderer::Renderer(std::string window_name)
{
    // Renderer Settings
    sf::ContextSettings sf_setting;
    sf_setting.antialiasingLevel = 8;

    // Create Window:
    _hrenderer = new sf::RenderWindow(
        sf::VideoMode(nw::Config::WINDOW_SIZE_INIT_X,
                      nw::Config::WINDOW_SIZE_INIT_Y),
        sf::String(window_name),
        this->_evalWindowStyle(),
        sf_setting);

    // Test on window Creation
    if (!_hrenderer)
    {
        // warning: Window is not created:
        nw::Util::RuntimeError(
            "[nw::Window::Renderer - Constructor] Failed to create window.");
    }
    else
    {
        // Window handle is successfully registed
        ____HERE_HAS_DEBUG_FUNCTION____
        nw::Util::DebugMessage(
            "[nw::Window::Renderer] - Register status: [ SUCCESS ]");
        // Print out window pointer heap address
        nw::Util::DebugMessageP(
            "- Window Renderer Registry",
            static_cast<void *>(_hrenderer));
    }

    // Create viewport set into window
    sf::View view(sf::FloatRect(0, 0,
                                (float)nw::Config::WINDOW_SIZE_INIT_X,
                                (float)nw::Config::WINDOW_SIZE_INIT_Y));
    _hrenderer->setView(view);
    _hrenderer->setFramerateLimit(nw::Config::WINDOW_VAR_FRAMELIMIT); 
    _hrenderer->setVerticalSyncEnabled(true);
}

//[Destructor]
nw::Window::Renderer::~Renderer()
{
    ____HERE_HAS_DEBUG_FUNCTION____
    nw::Util::DebugMessage("[nw::Window::Renderer] - Delete Window Handle");
    nw::Util::DebugMessageP("- Delete Renderer Window Handle",static_cast<void*>(_hrenderer));
    delete _hrenderer;
}

//[Window Resize -> In Refresh Loop]
void nw::Window::Renderer::Resize(hEvent h_event)
{
    if(h_event->type == sf::Event::Resized)
    {
        // update the view to the new size of the window
		auto now_size = _hrenderer->getSize();
		if ((int)now_size.x <= nw::Config::WINDOW_SIZE_MIN_X || (int)now_size.y <= nw::Config::WINDOW_SIZE_MIN_Y) {

			now_size.x = (unsigned int)std::max((int)now_size.x, (int)nw::Config::WINDOW_SIZE_MIN_X);
			now_size.y = (unsigned int)std::max((int)now_size.y, (int)nw::Config::WINDOW_SIZE_MIN_Y);
			_hrenderer->setSize(now_size);
		}

		sf::FloatRect visibleArea(0, 0, (float)h_event->size.width, (float)h_event->size.height);
		_hrenderer->setView(sf::View(visibleArea));
    }
}

//[Getter Function]
nw::hRenderer nw::Window::Renderer::GetHandle()
{
    return this->_hrenderer;
}




