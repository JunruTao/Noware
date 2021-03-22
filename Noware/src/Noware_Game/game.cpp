#include "Noware_Game/game.h"


std::vector<std::unique_ptr<sf::Drawable>> pool = {};

void nw::GR::InitPlayground()
{
    nw::Window::setInitSize(800,600);
    nw::Window::setMinSize(100,100);
    nw::Window::setResizable(false);
    nw::Window::setFullScreen(false);
    

    nw::Window::MasterRegister("First Noware Game");

    sf::CircleShape cir(100.f);
    cir.setFillColor(sf::Color::Green);
    
    sf::ConvexShape polygon(4);
    std::vector<sf::Vector2f> points = 
    {
        {0.0f, 0.0f},
        {100.0f, 0.0f},
        {100.0f, 100.0f},
        {0.0f, 100.0f}
    };
    sf::Transform mat(
    1, 0.5, 0,
    0, 1, 0,
    0, 0, 1);
    for(short i=0; i<4; i++)
    {
        points[i] = mat.transformPoint(points[i]);
        polygon.setPoint(i, points[i]);
    }

    polygon.setFillColor(sf::Color::Cyan);
    
    
    std::unique_ptr<sf::Drawable> shape(new sf::ConvexShape(std::move(polygon)));
    nw::PushSfmlGeo(shape);
}

void nw::GR::ProcessEvent(nw::hEvent h_event)
{
    //TODO:
}

void nw::GR::DrawCalls()
{
    nw::DrawSfmlGeo();
}