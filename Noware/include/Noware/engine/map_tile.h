#ifndef _MAP_TILE_H_
#define _MAP_TILE_H_


#include "Noware/graphics.h"
#include "Noware/engine/game_object.h"

namespace nw
{
    class MapTile: public Drawable, public GameObject
    {
    public:
        //[Constructor]
        MapTile();
        MapTile(float tile_size);
        //[Destructor]
        ~MapTile();

        //[MFunc ovrd]
        void Draw() override;
        //[MFunc ovrd]
        void Update() override;
    
    private:
        sf::ConvexShape _shape;
    };
}

#endif