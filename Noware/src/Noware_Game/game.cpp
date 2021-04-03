#include "Noware_Game/game.h"


void nw::GR::InitPlayground()
{
    nw::Window::setInitSize(800,600);
    nw::Window::setMinSize(100,100);
    nw::Window::setResizable(true);
    nw::Window::setFullScreen(false);
    
    nw::Window::MasterRegister("First Noware Game");
    nw::Map* map = new nw::Map(10,10,nw::Maptype::Diamond);
    nw::AddMap(map);

}

void nw::GR::ProcessEvent()
{
    //TODO:
}

void nw::GR::DrawCalls()
{
    nw::DrawMap();
}