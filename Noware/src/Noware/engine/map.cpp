#include "Noware/engine/map.h"
#include "Noware/engine/main_loop.h"
#include <cmath>

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
      _translation(sf::Vector2f(0,0)),
      _buffer_cached(false),
      _tile_size(tile_size),
      _size_x(sizex),
      _size_y(sizey),
      _mouselastTileIndex(-1)
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

    _LogHighlightShape();

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
//[Draw Call, unique for map object] PUB
void nw::Map::Draw()
{
    nw::Window::MasterRenderer->GetHandle()->draw(*_buffer_spr);

    // if there's selection of the tiles.
    if(_selectedTileIndex >=0)
    {
        nw::Window::MasterRenderer->GetHandle()->draw(_highlightShape);
    }
}


//{------------------------------------------------------------------------------}
//[Update Call, unique for map object] PUB
void nw::Map::Update()
{
    // Variables that shouldn't be freed all the time
    static float gridx = -1;
    static float gridy = -1;
    static float _gridx = -1;
    static float _gridy = -1;

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
            _buffer_spr->setPosition(_translation);
        }
        break;
    case sf::Event::MouseMoved:
        // moving a mouse, and test which tile is selected.

        //[Calculation of the diamond map transfrom to grid.]
        //1. subtract translation.
        //2. offset with _x_offset 0 <---
        //3. scale Y from (0,0) 2 times
        //4. rorate from (0,0) 45 degrees;
        //////---sin(45d) = 0.0137073546047074765840170910676‬
        //////---cos(45d) = 0.99990604980155050801971795294044
        // nX = x * cos45 - y * sin45;
        // nY = y * cos45 + x * sin45;

        if (this->_map_type == nw::Maptype::Grid)
        {
            // getting the grid profile location(subtract translate and divide by grid size)
            // then rounding the float to floor should get the natural number of the grid.
            gridx = (-_translation.x + (float)sf::Mouse::getPosition(*nw::Window::MasterRenderer->GetHandle()).x) / _tile_size;
            gridy = (-_translation.y + (float)sf::Mouse::getPosition(*nw::Window::MasterRenderer->GetHandle()).y) / _tile_size;
        }
        else //{Diamond shape layout}
        {
            _gridx = (float)sf::Mouse::getPosition(*nw::Window::MasterRenderer->GetHandle()).x - _translation.x - _diamondXOffset;
            _gridy = ( (float)sf::Mouse::getPosition(*nw::Window::MasterRenderer->GetHandle()).y - _translation.y) * 2;
            gridx = (( _gridx * cos45dgr) - (_gridy * sin45dgr));
            gridy = (( _gridy * cos45dgr) + (_gridx * sin45dgr));

            nw::Dbg::OverlayText.setPosition(gridx, gridy);

            gridx /= _tile_size;
            gridy /= _tile_size;
        }

        // when the mouse pos is in the map absolute space:
        _selectedTileIndex = (size_t)(floorf(gridy) * _size_x + floorf(gridx));

        // if the mouse postion can be mapped into the integer grid:
        if ((gridx >= 0 && gridx < _size_x) && (gridy >= 0 && gridy < _size_y))
        {
            if (_selectedTileIndex != _mouselastTileIndex)
            {
                nw::Dbg::OverlayText.setString(std::to_string(_selectedTileIndex));
                if(_map_type == nw::Maptype::Grid)
                    _highlightShape.setPosition(_maptiles[_selectedTileIndex]->getPostion() + _translation);
                else if(!_diamondsGridIndices.empty())
                    _highlightShape.setPosition(_maptiles[_diamondsGridIndices[_selectedTileIndex]]->getPostion() + _translation);
                else
                    nw::Util::RuntimeError("[nw::Map] failed process mouse move selection");
                _mouselastTileIndex = _selectedTileIndex;
            }
        }
        else
        {
            _selectedTileIndex = -1;
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
    
    // From the Bound to calculate the width and height of the map in screen space
    this->_map_texture_size = sf::Vector2f(max_x-min_x, max_y-min_y);
    
    // Moving the gird fully aligned to the top-left of the screen to render the buffer
    for (size_t i = 0; i < _maptiles.size(); ++i)
    {
        _maptiles[i]->Translate(sf::Vector2f(-min_x, -min_y));
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
//[MFunc PROT]
// Function:
/////This is a small util herlper function that might be replaced in further dev.
/////it centers the entire map the the 0.5-0.5 xy of the screen
void nw::Map::centerScreen()
{
    if(false)
    {
    
    sf::Vector2u screensize = nw::Window::MasterRenderer->GetHandle()->getSize();

    this->_translation = sf::Vector2f(
        ((float)screensize.x - _map_texture_size.x) * 0.5f,
        ((float)screensize.y - _map_texture_size.y) * 0.5f
    );
    _buffer_spr->setPosition(_translation);
    }
}

//{------------------------------------------------------------------------------}
//[MFunc PROT]
// Function:
/////After the sorting in the container, the order in the container should be set into
/////each tile's _drawing_index parameter.
void nw::Map::buildTileIndex()
{
    for (size_t i = 0; i < _maptiles.size(); ++i)
    {
        _maptiles[i]->setDrawingIndex(i);
    }
}



//{------------------------------------------------------------------------------}
//[MFunc PROT]
// Function:
/////Sorting the maptile container in Diamond fashion, build index as well
void nw::Map::sortDiamond()
{
    static bool diamond_indexed = false;

    //now the index of the vector is sorted.
    std::sort(_maptiles.begin(), _maptiles.end(), nw::MapTile::sortDiamond);

    if (!diamond_indexed)
    {
        std::vector<unsigned int> ind; // this will be the diamond index
        for (size_t i = 0; i < _maptiles.size(); ++i)
        {
            ind.push_back(i);
            // now this is real index, but in diamond order.
            _diamondsGridIndices.push_back(_maptiles[i]->getRealIndex());
        }
        // sort the diamond index into really index order.
        std::sort(ind.begin(), ind.end(), [&](unsigned int A, unsigned int B) {
            return _diamondsGridIndices[A] < _diamondsGridIndices[B];
        });
        _diamondsGridIndices = ind;

        diamond_indexed = true;
    }

    buildTileIndex();
}

//{------------------------------------------------------------------------------}
//[MFunc PROT]
// Function:
/////Sorting the maptile container in Grid fashion, build index as well
void nw::Map::sortGrid()
{
    std::sort(_maptiles.begin(), _maptiles.end(), nw::MapTile::sortGird);
    buildTileIndex();
}

//{------------------------------------------------------------------------------}
//[MFunc PROT]
// Function:
/////This function allow this map to switch the mode between the layouts, now it it's
/////more of a toggle that the layouts are Grid and diamond. it will run through all
/////the map tiles and update the shape internally, then sorting the drawing order in
/////the sort functions accordingly.
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

    // the highlight shape should be relogged.
    _LogHighlightShape();
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
//[MFunc] PRIV
//// Function:
//////get the first shape of the map tile, and take that as _highlightShape
void nw::Map::_LogHighlightShape()
{
    // here stores the first map tiles shape
    _highlightShape = _maptiles[0]->getShape();
    _highlightShape.setOutlineThickness(0);
    _highlightShape.setFillColor(sf::Color(255,255,255,100));

    if(_map_type == nw::Maptype::Diamond)
    {
        _diamondXOffset = _highlightShape.getPosition().x;

    }

    // note:
    //// not only in the constructor, everytime the layout changing shoud
    //// trigger this and set it back to -1;
    _selectedTileIndex = -1;
}