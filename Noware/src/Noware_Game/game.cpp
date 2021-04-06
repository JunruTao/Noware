#include "Noware_Game/game.h"


void nw::GR::InitPlayground()
{
    nw::Window::setInitSize(800,600);
    nw::Window::setMinSize(100,100);
    nw::Window::setResizable(true);
    nw::Window::setFullScreen(false);
    
    nw::Window::MasterRegister("First Noware Game");
    nw::Map* map = new nw::Map(20, 10, 70, nw::Maptype::Diamond);
    nw::AddMap(map);
}

void nw::GR::ProcessEvent()
{
    nw::GeoPool::Maps[0]->Update();
}

void nw::GR::DrawCalls()
{
    nw::DrawMap();
}