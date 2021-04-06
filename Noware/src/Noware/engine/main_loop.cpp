#include "Noware/engine/main_loop.h"


//[Local Function]
nw::hRenderer _getRenderer()
{
    return nw::Window::MasterRenderer->GetHandle();
}


//[GLOBAL VAR] init data pool: SFML
std::vector<std::unique_ptr<sf::Drawable>> nw::GeoPool::SFML = {};
//[GLOBAL] Maps container declare.
//{NOTE:}
// Here all the maps are allocated as normal heap pointers
std::vector<nw::Map*> nw::GeoPool::Maps = {};


//{----------------------------SFML HELPER DRAWERS--------------------------------}
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

//{----------------------------MAP DRAWING FUNCTIONS--------------------------------}

//[GLOBAL]
size_t nw::AddMap(nw::Map*& map_ptr)
{
    nw::GeoPool::Maps.emplace_back(std::move(map_ptr));
    return nw::GeoPool::Maps.size()-1;
}

//[GLOBAL]
void nw::DrawMap()
{
    if(!nw::GeoPool::Maps.empty())
    {
        nw::GeoPool::Maps[nw::GeoPool::Maps.size()-1]->Draw();
    }
}

//[GLOBAL]
void nw::DrawMap(size_t index)
{
    if(!nw::GeoPool::Maps.empty() && index <= nw::GeoPool::Maps.size()-1)
    {
        nw::GeoPool::Maps[index]->Draw();
    }
}

//[GLOBAL]



// [ LOCAL ] Free the memory of the maps
void lFreeMap()
{
    if(!nw::GeoPool::Maps.empty())
    {
        for(int i = 0; i < nw::GeoPool::Maps.size(); ++i)
        {
            delete nw::GeoPool::Maps[i];
        }
    }
}



//[Definition of ProgramLoop function]
// This is function should be called in the creator function.
void nw::ProgramLoop()
{////START OF Programe Loop

    //[Init The FontManager]
    nw::MasterFontManager = std::make_shared<nw::FontManager>();

    //[User Init Field]
    /////Make sure global resources are intialised before this field
    nw::GR::InitPlayground();
    
    //[Checker]
    /////Checking if the window was created correctly
    if(!nw::Window::MasterRenderer)
    {
        nw::Util::RuntimeError("[Fatal Error] The Renderer Object is not created");
        return;
    }

    

    //[THE BIG WHILE LOOP]
    while(_getRenderer()->isOpen())
    {
        // Process events
		nw::Window::MasterhEvent = new sf::Event;
        while(_getRenderer()->pollEvent(*nw::Window::MasterhEvent))
        {
            if(nw::Window::MasterhEvent->type == sf::Event::Closed || nw::Window::MasterhEvent->key.code == sf::Keyboard::Escape)
            {
                _getRenderer()->close();
                break;
            }
            // defined Global
            nw::GR::ProcessEvent();
            nw::Window::MasterRenderer->Resize(nw::Window::MasterhEvent);
        }
        // Defined Global
        _getRenderer()->clear();
        nw::GR::DrawCalls();
        _getRenderer()->display();
    }


    //[FREE RESOURCE]
    // Deleting the window object here
    delete nw::Window::MasterRenderer;
    delete nw::Window::MasterhEvent;
    lFreeMap();
    

    nw::Util::DebugExitPause();
}////END OF Programe Loop