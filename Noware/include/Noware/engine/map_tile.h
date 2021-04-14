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
        // default constructor.
        ////\param tile_size (float) the w/h of the square
        ////\param cord (nw::Vec2i&) coordinate in integer, i.g.{2, 4} x,y
        ////\param type (nw::Maptype) enum
        MapTile(float tile_size, nw::Vec2i &cord, nw::Maptype type=Maptype::Grid);
        
        //[Destructor]
        // destructor 
        ~MapTile();

        //[MFunc ovrd]
        void Draw() override;

        //[MFunc ovrd]
        void Update() override;

        //[MFunc] PUB
        // Function:
        /////Custom Draw, Draw tiles to a buffer.
        void Draw(sf::RenderTexture& buffer_renderer);

        //[MFunc] PUB Getter 
        /////-> Get X Coordinate
        ////\return (int)
        int getCordX();
        
        //[MFunc] PUB Getter 
        /////-> Get Y Coordinate
        ////\return (int)
        int getCordY();
        
        //[MFunc] PUB Getter 
        /////-> Get Coordinate Vector(Vec2i)
        ////\return (nw::Vec2i)
        nw::Vec2i getCordVec();

        //[MFunc] PUB Getter 
        /////-> Get Minimum bound
        ////\return (sf::Vector2f) min point2D
        sf::Vector2f getBoundMin();

        //[MFunc] PUB Getter 
        /////-> Get Maxmum bound
        ////\return (sf::Vector2f) max point2D
        sf::Vector2f getBoundMax();


        //[MFunc] PUB Getter
        /////-> Get Shape data(4 sided convex shape)
        ////\return (sf::ConvexShape)
        sf::ConvexShape getShape() const;


        //[MFunc] PUB Getter
        /////-> Get local screen position(sprite unmoved)
        ////\return (sf::Vector2f){x,y}
        sf::Vector2f getPostion() const;

        //[MFunc] PUB Setter
        // Using translate all the shapes in this object by a vector
        ////\param motion (sf::Vector2f) a 2D float vector
        void Translate(sf::Vector2f motion);
    
        //[MFunc] PUB Setter
        /////Set the index. (for now it just a helper function for display purpose)
        void setIndex(unsigned int index);


        // a type def to simplify the parameter field
        typedef std::unique_ptr<MapTile>& umtr;
        typedef std::shared_ptr<MapTile>& smtr;

        //[Static MFunc]
        // sorting the map tiles' drawing order in diamond mode
        static bool sortDiamond(smtr t1, smtr t2);
        
        //[Static MFunc]
        // sorting the map tiles' drawing order in grid mode
        static bool sortGird(smtr t1, smtr t2);

        void ConstructGrid();
        void ConstructDiamond();

    protected:
        void updateLabel();

    private:
        sf::ConvexShape _shape;
        sf::Text _label;
        float _tilesize;
        nw::Vec2i _cord_i;
        size_t _index;
        size_t _drawing_index;

        //[Staic Member]
        //// Storing the amount of index.
        static size_t _tile_count;
    };
}

#endif