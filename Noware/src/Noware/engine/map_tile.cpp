#include "Noware/engine/map_tile.h"

//[Static MVar] Declare
size_t nw::MapTile::_tile_count = 0;

void nw::MapTile::updateLabel()
{
    _label.setString(sf::String(std::to_string(_drawing_index)));
    _label.setOrigin(
        _label.getLocalBounds().width / 2,
        _label.getLocalBounds().height);

    _label.setPosition(_shape.getPosition());
}



/////Construct Grid shape
void nw::MapTile::ConstructGrid()
{
    //creating the square
    _shape.setPoint(0, sf::Vector2f(0, 0));
    _shape.setPoint(1, sf::Vector2f(_tilesize, 0));
    _shape.setPoint(2, sf::Vector2f(_tilesize, _tilesize));
    _shape.setPoint(3, sf::Vector2f(0, _tilesize));

    //offset to the tile position
    _shape.setOrigin(_tilesize / 2, _tilesize / 2);
    _shape.setPosition((float)_cord_i.x * _tilesize, (float)_cord_i.y * _tilesize);

    updateLabel();
}

/////Construct Diamond Shape
void nw::MapTile::ConstructDiamond()
{
    // Note:
    //// The Diamond shape is that the square rotated 45 degree then scaled 0.5 times
    //// from the global Y scale from origin.
    float _diag = _tilesize / SqrtOf2;

    _shape.setPoint(0, sf::Vector2f(0, 0));
    _shape.setPoint(1, sf::Vector2f(_diag, _diag * 0.50f));
    _shape.setPoint(2, sf::Vector2f(0, _diag));
    _shape.setPoint(3, sf::Vector2f(-_diag, _diag * 0.50f));

    //offset to the tile position
    _shape.setOrigin(0, _diag * 0.50f);
    _shape.setPosition(
        (_diag * (float)_cord_i.x) - (_diag * (float)_cord_i.y),
        ((_diag * (float)_cord_i.x) + (_diag * (float)_cord_i.y)) * 0.5f);

    updateLabel();
}

//[Constructor]
nw::MapTile::MapTile(float tile_size, nw::Vec2i &cord, nw::Maptype type)
    : _cord_i(cord), _tilesize(tile_size)
{
    // This index will start from 0 to count;
    _index = _tile_count;
    _drawing_index = _index;
    ++_tile_count;

    //[For display a the index of the tiles]
    _label.setCharacterSize(30.0f);
    _label.setFont(*nw::MasterFontManager->GetFont(DEFAULT_FONTNAME));

    //createing the shape.
    _shape = sf::ConvexShape(4);
    //previewing the grids
    _shape.setOutlineColor(sf::Color(255, 255, 255));
    _shape.setOutlineThickness(1);
    _shape.setFillColor(sf::Color::Transparent);


    if (type == nw::Maptype::Grid)
    {
        ConstructGrid();
    }
    else if (type == nw::Maptype::Diamond)
    {
        ConstructDiamond();
    }

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
    //not perferred, unless is constantly flashing or moving object.
    nw::Window::MasterRenderer->GetHandle()->draw(this->_shape);
    nw::Window::MasterRenderer->GetHandle()->draw(this->_label);
}

void nw::MapTile::Draw(sf::RenderTexture& buffer_renderer)
{
    //drawing to a back buffer.
    buffer_renderer.draw(this->_shape);
    buffer_renderer.draw(this->_label);
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
    this->_drawing_index = index;
    this->_label.setString(std::to_string(_drawing_index));
}


//[Static MFunc]
// Declearation.
bool nw::MapTile::sortDiamond(smtr t1,smtr t2)
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

//[Static MFunc]
// Declearation.
bool nw::MapTile::sortGird(smtr t1,smtr t2)
{
    return t1->_index < t2->_index;
}

//[Getter]
sf::Vector2f nw::MapTile::getBoundMin()
{
    return sf::Vector2f(
        _shape.getGlobalBounds().left, 
        _shape.getGlobalBounds().top);
}
sf::Vector2f nw::MapTile::getBoundMax()
{
    return sf::Vector2f(
        _shape.getGlobalBounds().left + _shape.getGlobalBounds().width,
        _shape.getGlobalBounds().top + _shape.getGlobalBounds().height);    
}

//[Transform function]
void nw::MapTile::ViewTranslate(sf::Vector2f motion)
{
    this->_shape.setPosition(
        _shape.getPosition().x + motion.x,
        _shape.getPosition().y + motion.y);

    this->_label.setPosition(
        _label.getPosition().x + motion.x,
        _label.getPosition().y + motion.y);
}