#include "Noware/engine/map_tile.h"

//[Static MVar] Declare
size_t nw::MapTile::_tile_count = 0;

void nw::MapTile::updateLabel()
{
    //{NOTE}
    // this lable is currently for displaying the _drawing_index
    // bigger numbers shown indicates the layer is higher.
    _label.setString(sf::String(std::to_string(_index)));
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
    
    //{NOTE}
    // (1)The Index will be be a static sorting, increase in X and then new line in Y
    // as it will always be a sorted grid layout fashion;
    // (2)Drawing index will be the order of drawing.
    _index = _tile_count;
    _drawing_index = _index;

    //{NOTE}
    // This count is static, globally shared with other tiles in map/maps, 
    // will start from 0 to count, indicates how many instances of this object;
    ++_tile_count;

    //{NOT}
    // _label -> For display a the index of the tiles
    // for better previewing the grids
    _label.setCharacterSize(30.0f);
    _label.setFont(*nw::MasterFontManager->GetFont(DEFAULT_FONTNAME));

    // createing the shape.
    _shape = sf::ConvexShape(4);
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
    // drawing to a back buffer.
    buffer_renderer.draw(this->_shape);
    buffer_renderer.draw(this->_label);
    //{NOTE}
    // this draw call is called very few times, it only happens if there's
    // changes in the tiles needs to be updated. therefore, this function will be
    // called during: 1. index change, layout change
    // 2. texture update, or similar tasks.

    // the map transform will transfer the buffer instead of these tile objects.
}

//[Update call ovrd]
void nw::MapTile::Update()
{
    // currently not called.
}

//[Getter Functions section]
// ---------------------------------------------------

//[GETTER] PUB MFUNC
// Get the  Int X Coordinate
int nw::MapTile::getCordX()
{
    return _cord_i.x;
}

//[GETTER] PUB MFUNC
// Get the Int Y Coordinate
int nw::MapTile::getCordY()
{
    return _cord_i.y;
}

//[GETTER] PUB MFUNC
// Get the Int Vector Coordinate
nw::Vec2i nw::MapTile::getCordVec()
{
    return _cord_i;
}

//[GETTER] PUB MFUNC
// Get the Bound min
sf::Vector2f nw::MapTile::getBoundMin()
{
    return sf::Vector2f(
        _shape.getGlobalBounds().left, 
        _shape.getGlobalBounds().top);
}

//[GETTER] PUB MFUNC
// Get the Bound Max
sf::Vector2f nw::MapTile::getBoundMax()
{
    return sf::Vector2f(
        _shape.getGlobalBounds().left + _shape.getGlobalBounds().width,
        _shape.getGlobalBounds().top + _shape.getGlobalBounds().height);    
}

//[MFunc] PUB Getter
/////-> Get Shape data(4 sided convex shape)
////\return (sf::ConvexShape)
sf::ConvexShape nw::MapTile::getShape() const
{
    return _shape;
}

//[MFunc] PUB Getter
/////-> Get local screen position(sprite unmoved)
////\return (sf::Vector2f){x,y}
sf::Vector2f nw::MapTile::getPostion() const
{
    return this->_shape.getPosition();
}

//[MFunc] PUB Getter
/////-> Get the really index
////\return index(uint)
unsigned int nw::MapTile::getRealIndex() const
{
    return _index;
}

//[Setter Functions section]
// ---------------------------------------------------

//[SETTER] PUB MFUNC
// from the new index to overwrite the drawing index.
////\param index (uint)new index 
void nw::MapTile::setDrawingIndex(unsigned int index)
{
    this->_drawing_index = index;
    updateLabel();
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


//[Transform function]
void nw::MapTile::Translate(sf::Vector2f motion)
{
    this->_shape.setPosition(
        _shape.getPosition().x + motion.x,
        _shape.getPosition().y + motion.y);

    this->_label.setPosition(
        _label.getPosition().x + motion.x,
        _label.getPosition().y + motion.y);
}