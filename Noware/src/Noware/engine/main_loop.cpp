#include "Noware/engine/main_loop.h"


//[Local Function]
nw::hRenderer _getRenderer()
{
    return nw::Window::MasterRenderer->GetHandle();
}


//[GLOBAL VAR] init data pool: SFML
std::vector<std::unique_ptr<sf::Drawable>> nw::GeoPool::SFML = {};

//[GLOBAL]
void nw::PushSfmlGeo(std::unique_ptr<sf::Drawable>& uptr_sfDrawable)
{
    nw::GeoPool::SFML.emplace_back(std::move(uptr_sfDrawable));
}

//[GLOBAL]
void nw::DrawSfmlGeo()
{
    if(!nw::GeoPool::SFML.empty())
    {
        for(size_t i = 0; i < nw::GeoPool::SFML.size(); ++i)
        {
            _getRenderer()->draw(*nw::GeoPool::SFML[i]);
        }
    }
}



//[Definition of ProgramLoop function]
// This is function should be called in the creator function.
void nw::ProgramLoop()
{////START OF Programe Loop

    nw::GR::InitPlayground();
    if(!nw::Window::MasterRenderer)
    {
        nw::Util::RuntimeError("[Fatal Error] The Renderer Object is not created");
        return;
    }

    //[THE BIG WHILE LOOP]
    while(_getRenderer()->isOpen())
    {
        // Process events
		sf::Event event;
        while(_getRenderer()->pollEvent(event))
        {
            if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                _getRenderer()->close();
                break;
            }
            // defined Global
            nw::GR::ProcessEvent(&event);
            nw::Window::MasterRenderer->Resize(&event);
        }
        // Defined Global
        _getRenderer()->clear();
        nw::GR::DrawCalls();
        _getRenderer()->display();
    }


    //[FREE RESOURCE]
    // Deleting the window object here
    delete nw::Window::MasterRenderer;

    nw::Util::DebugExitPause();
}////END OF Programe Loop