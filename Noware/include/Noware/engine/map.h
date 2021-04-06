#ifndef _MAP_H_
#define _MAP_H_
#include "Noware/utility.h"
#include "Noware/graphics.h"
#include "Noware/engine/map_tile.h"

namespace nw
{
    class Map
    {
    public:
        //[Constructor]
        // Default constructor for the map object
        ////\param sizex elements of x direction
        ////\param sizey elements of y direction
        ////\param type enum[nw::Maptype], Grid or Diamond
        Map(unsigned int sizex, unsigned int sizey, float tile_size, nw::Maptype type = nw::Maptype::Grid);
        
        //[Destructor]
        ~Map();

        //[Draw Call, unique for map object] PUB
        void Draw();

        //[Updatem, unique for map object] PUB
        void Update();

    protected:
        //[MFunc PROT] Calculate Map Bound(w, h)
        // Function:
        /////1. Calculate the min/max corners of all the map tiles just created.
        /////2. Calculate the width and height of the map stored in _map_texture_size
        /////3. View translate each tile, making the entire map fit-aligned with top-left.
        void calcBound();

        //[MFunc PROT] Cache Map drawing to framebuffer
        // Function:
        /////Caching the texture to _buffer. this function should be called if there's any
        /////Drawing changes in any tile. if only happens to translation of the map, then
        /////Caching is not needed. 
        void cacheTexture();

        //[MFunc PROT]
        // Function:
        /////Caching 
        void centerScreen();

        //[MFunc PROT]
        // Function:
        /////Caching 
        void switchLayout();

        //[MFunc PROT]
        // Function:
        /////Caching 
        void sortDiamond();

        //[MFunc PROT]
        // Function:
        /////Caching 
        void sortGrid();

        //[MFunc PROT]
        // Function:
        /////Caching 
        void buildTileIndex();

        //[Static MVar]
        //{Global Map's texture renderer object}
        // use this object to render map elements to framebuffer.
        static sf::RenderTexture _buffer_renderer;
    
    private:
        //[MVar] container
        //// stores the map tiles objects as shared pointers.
        std::vector<std::shared_ptr<nw::MapTile>> _maptiles;

        //[MVar]
        //// a 2d float vector storing the width and height of the map
        sf::Vector2f _map_texture_size;
        //[MVar]
        //// every changes or construction of the map object will be renderer as 
        //// a framebuffer to this texture buffer object(sf).
        sf::Texture _buffer;

        //[MVar]
        //// Buffer Sprite, in order to draw the cached sreen buffer, a sprite will be
        //// constructed, (here using a heap resource, i.o.t. avoid creating a new sprite
        //// every draw calls), in the `cacheTexture` function will engage a delete/new to
        //// avoid memory leak in here.
        sf::Sprite* _buffer_spr;
        
        //[MVar]
        //// This is a dummy bool mechanism to prevent memory leak. when the constructor of
        //// the Map object is called, the _buffer_spr will not be a vaild pointer, that's
        //// the first time caching the _buffer_spr, and after that, all the updated sprite
        //// pointer will be deleted and new again from the _buffer.
        bool _buffer_cached;

        //[MVar]
        //// the offset translation of the map sprite from the screen o(0,0), should be stored
        //// in this variable always.
        sf::Vector2f _traslation;

        //[MVar]
        //// local id for the map_type(enum)
        nw::Maptype _map_type;
    };
}



#endif