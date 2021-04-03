#include "Noware/engine/map.h"


nw::Map::Map(unsigned int sizex, unsigned int sizey, nw::Maptype type)
{
    nw::Util::DebugCallerConstructor("Map");
    for (size_t y = 0; y < sizey; ++y)
    {
        for (size_t x = 0; x < sizex; ++x)
        {
            nw::Vec2i cord = {(int)x, (int)y};
            this->_maptiles.emplace_back(std::make_unique<nw::MapTile>(60, cord, type));
        }
    }
    if (type == nw::Maptype::Diamond)
    {
        std::sort(_maptiles.begin(), _maptiles.end(), nw::MapTile::sortDiamond);
        for(size_t i = 0; i < _maptiles.size(); ++i)
        {
            _maptiles[i]->setIndex(i);
        }
    }
}

nw::Map::~Map()
{
    nw::Util::DebugCallerConstructor("Map");
}

void nw::Map::Draw() const
{
    for(size_t i = 0; i < _maptiles.size(); ++i)
    {
        _maptiles[i]->Draw();
    }
}

void nw::Map::Update()
{

}