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

        //[Update, unique for map object] PUB
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
        /////This is a small util herlper function that might be replaced in further dev.
        /////it centers the entire map the the 0.5-0.5 xy of the screen 
        void centerScreen();

        //[MFunc PROT]
        // Function:
        /////This function allow this map to switch the mode between the layouts, now it it's
        /////more of a toggle that the layouts are Grid and diamond. it will run through all 
        /////the map tiles and update the shape internally, then sorting the drawing order in
        /////the sort functions accordingly. 
        void switchLayout();

        //[MFunc PROT]
        // Function:
        /////Sorting the maptile container in Diamond fashion, build index as well
        void sortDiamond();

        //[MFunc PROT]
        // Function:
        /////Sorting the maptile container in Grid fashion, build index as well
        void sortGrid();

        //[MFunc PROT]
        // Function:
        /////After the sorting in the container, the order in the container should be set into
        /////each tile's _drawing_index parameter. 
        void buildTileIndex();

        //[Static MVar]
        //{Global Map's texture renderer object}
        // use this object to render map elements to framebuffer.
        static sf::RenderTexture _buffer_renderer;
    
    private:
        //[MVar] container
        //// stores the map tiles objects as shared pointers.
        std::vector<std::shared_ptr<nw::MapTile>> _maptiles;


        //[MFunc] PRIV
        //// Function:
        //////get the first shape of the map tile, and take that as _highlightShape
        void _LogHighlightShape();

        //[MVar]
        ///// get the (selection) highlight unit shape
        sf::ConvexShape _highlightShape;

        //[MVar]
        //// a 2d float vector storing the width and height of the map
        sf::Vector2f _map_texture_size;
        //[MVar]
        //// every changes or construction of the map object will be renderer as 
        //// a framebuffer to this texture buffer object(sf).
        sf::Texture _buffer;

        //[MVar]
        //// Buffer Sprite, in order to draw the cached screen buffer, a sprite will be
        //// constructed, (here using a heap resource, i.o.t. avoid creating a new sprite
        //// every draw calls), in the `cacheTexture` function will engage a delete/new to
        //// avoid memory leak in here.
        sf::Sprite* _buffer_spr;
        
        //[MVar]
        //// This is a dummy bool mechanism to prevent memory leak. when the constructor of
        //// the Map object is called, the _buffer_spr will not be a valid pointer, that's
        //// the first time caching the _buffer_spr, and after that, all the updated sprite
        //// pointer will be deleted and new again from the _buffer.
        bool _buffer_cached;

        //[MVar]
        //// the offset translation of the map sprite from the screen o(0,0), should be stored
        //// in this variable always.
        sf::Vector2f _translation;

        //[MVar]
        //// local id for the map_type(enum)
        nw::Maptype _map_type;

        //[MVar]
        //// tile size
        float _tile_size;

        //[MVar]
        //// X dimension (positive integer)
        size_t _size_x;

        //[MVar]
        //// Y dimension (positive integer)
        size_t _size_y;

        //[MVar]
        //// Last Index (the last maptile the mouse was in)
        int _mouselastTileIndex;

        //[MVar]
        int _selectedTileIndex;
    };
}



#endif