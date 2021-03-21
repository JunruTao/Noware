#include "Noware_Game/game.h"

int main() 
{
    gameTest();
    nw::Window::setInitSize(800,600);
    nw::Window::setMinSize(100,100);
    nw::Window::setFullScreen(false);
    nw::Window::Renderer renderer("Noware");
	
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (renderer.GetHandle()->isOpen())
    {
        sf::Event event;
        while (renderer.GetHandle()->pollEvent(event))
        {
            renderer.Resize(&event);
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                renderer.GetHandle()->close();
        }

        renderer.GetHandle()->clear();
        renderer.GetHandle()->draw(shape);
        renderer.GetHandle()->display();
    }
    
    nw::Util::DebugExitPause();
    return 0;
}