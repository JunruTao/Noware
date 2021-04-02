#include "Noware_Game/game.h"


std::vector<std::unique_ptr<sf::Drawable>> pool = {};

void nw::GR::InitPlayground()
{
    nw::Window::setInitSize(800,600);
    nw::Window::setMinSize(100,100);
    nw::Window::setResizable(false);
    nw::Window::setFullScreen(false);
    


    nw::Window::MasterRegister("First Noware Game");

    nw::MapTile maptile;

    //Some SF shape test here.
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
    1, 0, 0,
    0, 1, 0,
    0, 0, 1);
    mat.rotate(45.0f);

    sf::Transform mat2(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1);
    
    mat2.scale(sf::Vector2f(1,0.5),sf::Vector2f(0, 0));
    for(short i=0; i<4; i++)
    {
        points[i] = mat.transformPoint(points[i]);
        points[i] = mat2.transformPoint(points[i]);
        polygon.setPoint(i, points[i]);
    }

    polygon.setFillColor(sf::Color::Cyan);
    
    
    std::unique_ptr<sf::Drawable> shape(new sf::ConvexShape(std::move(polygon)));
    nw::PushSfmlGeo(shape);
}

void nw::GR::ProcessEvent()
{
    //TODO:
}

void nw::GR::DrawCalls()
{
    nw::DrawSfmlGeo();
}