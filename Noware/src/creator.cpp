#include "Noware_Game/game.h"

int main() 
{
    gameTest();
    nw::Window::Renderer renderer("Noware");
	
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (renderer.GetHandle()->isOpen())
    {
        sf::Event event;
        while (renderer.GetHandle()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                renderer.GetHandle()->close();
        }

        renderer.GetHandle()->clear();
        renderer.GetHandle()->draw(shape);
        renderer.GetHandle()->display();
    }
    

    return 0;
}