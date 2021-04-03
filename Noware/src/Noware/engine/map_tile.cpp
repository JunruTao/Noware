#include "Noware/engine/map_tile.h"

//[Static MVar] Declare
size_t nw::MapTile::_tile_count = 0;

//[Constructor]
nw::MapTile::MapTile(float tile_size, nw::Vec2i &cord, nw::Maptype type)
    : _cord_i(cord)
{
    // This index will start from 0 to count;
    this->_index = _tile_count;
    ++_tile_count;

    //createing the shape.
    _shape = sf::ConvexShape(4);

    if (type == nw::Maptype::Grid)
    {
        //creating the square
        _shape.setPoint(0, sf::Vector2f(0, 0));
        _shape.setPoint(1, sf::Vector2f(tile_size, 0));
        _shape.setPoint(2, sf::Vector2f(tile_size, tile_size));
        _shape.setPoint(3, sf::Vector2f(0, tile_size));

        //offset to the tile position
        _shape.setOrigin(tile_size / 2, tile_size / 2);
        _shape.setPosition((float)_cord_i.x * tile_size, (float)_cord_i.y * tile_size);
    }
    else if (type == nw::Maptype::Diamond)
    {
        // Note:
        //// The Diamond shape is that the square rotated 45 degree then scaled 0.5 times
        //// from the global Y scale from origin. 
        float _diag = tile_size/SqrtOf2;

        _shape.setPoint(0, sf::Vector2f(0, 0));
        _shape.setPoint(1, sf::Vector2f(_diag, _diag * 0.50f));
        _shape.setPoint(2, sf::Vector2f(0, _diag));
        _shape.setPoint(3, sf::Vector2f(-_diag, _diag * 0.50f));

        //offset to the tile position
        _shape.setOrigin(0, _diag * 0.50f);
        _shape.setPosition(
            (_diag * (float)_cord_i.x) - (_diag * (float)_cord_i.y), 
            ((_diag * (float) _cord_i.x) + (_diag * (float)_cord_i.y))*0.5f
        );
    }

    //previewing the grids
    _shape.setOutlineColor(sf::Color(255, 255, 255));
    _shape.setOutlineThickness(1);
    _shape.setFillColor(sf::Color::Transparent);


    //[For display a the index of the tiles]
    _label.setCharacterSize(10.0f);
    _label.setFont(*nw::MasterFontManager->GetFont(DEFAULT_FONTNAME));
    _label.setPosition(_shape.getPosition());
    _label.setString(sf::String(std::to_string(_index)));
}

//[Destructor]
nw::MapTile::~MapTile()
{
    --_tile_count;
    //nw::Util::DebugCallerDestructor("MapTile");
}

//[Draw call ovrd]
void nw::MapTile::Draw()
{
    nw::Window::MasterRenderer->GetHandle()->draw(this->_shape);
    nw::Window::MasterRenderer->GetHandle()->draw(this->_label);
}

//[Update call ovrd]
void nw::MapTile::Update()
{
    
}

//[Getter Functions section]
// ---------------------------------------------------
int nw::MapTile::getCordX() { return _cord_i.x; }
int nw::MapTile::getCordY() { return _cord_i.y; }
nw::Vec2i nw::MapTile::getCordVec() { return _cord_i; }

//[Setter Functions section]
// ---------------------------------------------------
void nw::MapTile::setIndex(unsigned int index)
{
    this->_index = index;
    this->_label.setString(std::to_string(_index));
}


//[Static MFunc]
// Declearation.
bool nw::MapTile::sortDiamond(umtr &t1,umtr &t2)
{
    int t1sum = t1->getCordX() + t1->getCordY();
    int t2sum = t2->getCordX() + t2->getCordY();
    if (t1sum < t2sum)
    {
        return true;
    }
    else if (t1sum > t2sum)
    {
        return false;
    }
    else
    {
        //TODO: Temp xyzdir;
        // Here is for flipping the direction of the parallel overlap
        if (true)
        {
            return (t1->getCordX() < t2->getCordX());
        }
        else
        {
            return (t1->getCordY() < t2->getCordY());
        }
    }
}