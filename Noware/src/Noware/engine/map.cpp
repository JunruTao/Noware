#include "Noware/engine/map.h"


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//--+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+-
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//################################################################################
//******************************-DECLARE STATIC-**********************************
/*                                                                              */
/*                                                                              */
//{------------------------------------------------------------------------------}
//[Static Map's buffer renderer] Declear
sf::RenderTexture nw::Map::_buffer_renderer;


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//--+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+-
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//################################################################################
//***************************-CONSTRUCTORS & DESTR.-******************************
/*                                                                              */
/*                                                                              */
//{------------------------------------------------------------------------------}
//[MAP's Constructor]
// Default constructor for the map object
////\param sizex elements of x direction
////\param sizey elements of y direction
////\param type enum[nw::Maptype], Grid or Diamond
// -
nw::Map::Map(unsigned int sizex, unsigned int sizey, float tile_size, nw::Maptype type)
    : _map_type(type),
      _buffer_cached(false)
{
    ____HERE_HAS_DEBUG_FUNCTION____
    nw::Util::DebugCallerConstructor("Map");

    // construct a tile increase in X then Y.
    for (size_t y = 0; y < sizey; ++y)
    {
        for (size_t x = 0; x < sizex; ++x)
        {
            nw::Vec2i cord = {(int)x, (int)y};
            this->_maptiles.emplace_back(std::make_shared<nw::MapTile>(tile_size, cord, type));
        }
    }

    calcBound();

    if (type == nw::Maptype::Diamond)
    {
        sortDiamond();
    }
    cacheTexture();
    centerScreen();
}

//{------------------------------------------------------------------------------}
//[MAP's Destructor]
// Destructor, REMEMBER TO FREE MEMORIES. RAII
nw::Map::~Map()
{

    ____HERE_HAS_DEBUG_FUNCTION____
    nw::Util::DebugCallerConstructor("Map");
    nw::Util::DebugMessageP(
            "[nw::Map]Deleted Sprite",
            static_cast<void *>(_buffer_spr));

    // free the sprite, prevent memory leak.
    delete _buffer_spr;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//--+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+-
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//################################################################################
//******************************-PUBLIC MFUNCS-***********************************
/*                                                                              */
/*                                                                              */
//{------------------------------------------------------------------------------}
void nw::Map::Draw()
{
    nw::Window::MasterRenderer->GetHandle()->draw(*_buffer_spr);
}


//{------------------------------------------------------------------------------}
void nw::Map::Update()
{
    switch (nw::Window::MasterhEvent->type)
    {
    case sf::Event::Resized:
        centerScreen();
        break;
    case sf::Event::KeyPressed:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            switchLayout();
            cacheTexture();

            _buffer_spr->setPosition(_traslation);
        }
        break;
    default:
        break;
    }
}



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//--+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+-
//+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
//################################################################################
//****************************-PROTECTED MFUNCS-**********************************
/*                                                                              */
/*                                                                              */
//{------------------------------------------------------------------------------}
//[MFunc PROTECTED] Calculate the Bound. 
// Function:
/////1. Calculate the min/max corners of all the map tiles just created.
/////2. Calculate the width and height of the map stored in _map_texture_size
/////3. View translate each tile, making the entire map fit-aligned with top-left.
void nw::Map::calcBound()
{
    float min_x = 0.f;
    float min_y = 0.f;
    float max_x = 0.f;
    float max_y = 0.f;
    for (size_t i = 0; i < _maptiles.size(); ++i)
    {
        sf::Vector2f cordmin = _maptiles[i]->getBoundMin();
        sf::Vector2f cordmax = _maptiles[i]->getBoundMax();
        min_x = std::min(cordmin.x, min_x);
        min_y = std::min(cordmin.y, min_y);
        max_x = std::max(cordmax.x, max_x);
        max_y = std::max(cordmax.y, max_y);
    }
    
    // From the Bound to cauculate the width and height of the map in screen space
    this->_map_texture_size = sf::Vector2f(max_x-min_x, max_y-min_y);
    
    // Moving the gird fully aligned to the top-left of the screen to render the buffer
    for (size_t i = 0; i < _maptiles.size(); ++i)
    {
        _maptiles[i]->ViewTranslate(sf::Vector2f(-min_x, -min_y));
    }
}

//{------------------------------------------------------------------------------}
//[MFunc PROTECTED] Cache Map drawing to framebuffer
// Function:
/////Caching the texture to _buffer. this function should be called if there's any
/////Drawing changes in any tile. if only happens to translation of the map, then
/////Caching is not needed.
void nw::Map::cacheTexture()
{
    if (!_maptiles.empty())
    {
        _buffer_renderer.create(_map_texture_size.x, _map_texture_size.y);
        _buffer_renderer.clear(sf::Color::Transparent);
        //Buffer's Draw call here..
        for (size_t i = 0; i < _maptiles.size(); ++i)
        {
            _maptiles[i]->Draw(_buffer_renderer);
        }
        _buffer_renderer.display();
        _buffer = _buffer_renderer.getTexture();
    }
    
    // Preventing Memory Leak 
    if(!_buffer_cached)
    {
        // creating new sprite from the buffer object.
        _buffer_spr = new sf::Sprite(_buffer);

        ____HERE_HAS_DEBUG_FUNCTION____
        nw::Util::DebugMessageP("[nw::Map]First Create Resource Map buffer Sprite", static_cast<void*>(_buffer_spr) );

        // The toggle is on, next time this resource should be freed.
        _buffer_cached = true;
    }else
    {
        // free the old texture.
        delete _buffer_spr;
        // creating new sprite from the buffer object.
        _buffer_spr = new sf::Sprite(_buffer);
        ____HERE_HAS_DEBUG_FUNCTION____
        nw::Util::DebugMessageP( "[nw::Map]Deleted Old Sprite, New Sprite", static_cast<void *>(_buffer_spr));
    }
}




//{------------------------------------------------------------------------------}
void nw::Map::buildTileIndex()
{
    for (size_t i = 0; i < _maptiles.size(); ++i)
    {
        _maptiles[i]->setIndex(i);
    }
}


//{------------------------------------------------------------------------------}
void nw::Map::sortDiamond()
{
    std::sort(_maptiles.begin(), _maptiles.end(), nw::MapTile::sortDiamond);
    buildTileIndex();
}


//{------------------------------------------------------------------------------}
void nw::Map::sortGrid()
{
    std::sort(_maptiles.begin(), _maptiles.end(), nw::MapTile::sortGird);
    buildTileIndex();
}












//{------------------------------------------------------------------------------}
void nw::Map::switchLayout()
{
    if(_map_type == nw::Maptype::Grid)
    {
        ____HERE_HAS_DEBUG_FUNCTION____
        nw::Util::DebugMessage("[nw::Map] Switch Layout to {Diamond}");
        for (size_t i = 0; i < _maptiles.size(); ++i)
        {
            _maptiles[i]->ConstructDiamond();
        }
        sortDiamond();
        calcBound(); 
        _map_type = nw::Maptype::Diamond;
    }
    else
    {
        ____HERE_HAS_DEBUG_FUNCTION____
        nw::Util::DebugMessage("[nw::Map] Switch Layout to {Grid}");
        for (size_t i = 0; i < _maptiles.size(); ++i)
        {
            _maptiles[i]->ConstructGrid();
        }
        sortGrid();
        calcBound();
        _map_type = nw::Maptype::Grid;
    }
}




//{------------------------------------------------------------------------------}
void nw::Map::centerScreen()
{
    sf::Vector2u screensize = nw::Window::MasterRenderer->GetHandle()->getSize();

    this->_traslation = sf::Vector2f(
        ((float)screensize.x - _map_texture_size.x) * 0.5f,
        ((float)screensize.y - _map_texture_size.y) * 0.5f
    );
    _buffer_spr->setPosition(_traslation);
}