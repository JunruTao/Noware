#ifndef _MAP_TILE_H_
#define _MAP_TILE_H_


#include "Noware/graphics.h"
#include "Noware/engine/game_object.h"

namespace nw
{
    enum class Maptype
    {
        Grid    = 0,
        Diamond = 1
    };


    class MapTile: public Drawable, public GameObject
    {
    public:
        //[Constructor]
        MapTile(float tile_size, nw::Vec2i &cord, nw::Maptype type=Maptype::Grid);
        //[Destructor]
        ~MapTile();

        //[MFunc ovrd]
        void Draw() override;
        //[MFunc ovrd]
        void Update() override;
        
        //[MFunc] PUB Getter 
        // -> Get X Coordinate
        int getCordX();
        //[MFunc] PUB Getter 
        // -> Get Y Coordinate
        int getCordY();
        //[MFunc] PUB Getter 
        // -> Get Coordinate Vector(Vec2i)
        nw::Vec2i getCordVec();
    
        //[MFunc] PUB Setter
        // -> Set the index. (for now it just a helper function for display purpose)
        void setIndex(unsigned int index);


        // a type def to simplify the parameter field
        typedef std::unique_ptr<MapTile>& umtr;

        //[Static MFunc]
        // sorting the map tiles' drawing order in diamond mode
        static bool sortDiamond(umtr t1, umtr t2);

    private:
        sf::ConvexShape _shape;
        sf::Text _label;
        nw::Vec2i _cord_i;
        size_t _index;

        //[Staic Member]
        //// Storing the amount of index.
        static size_t _tile_count;
    };
}

#endif