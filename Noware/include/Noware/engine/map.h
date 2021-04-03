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
        Map(unsigned int sizex, unsigned int sizey, nw::Maptype type = nw::Maptype::Grid);
        
        //[Destructor]
        ~Map();

        //[Draw Call, unique for map object]
        void Draw() const;

        //[Updatem, unique for map object]
        void Update();


    private:
        std::vector<std::unique_ptr<nw::MapTile>> _maptiles;
    };
}



#endif