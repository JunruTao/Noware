#include "Noware/engine/game_object.h"


nw::GameObject::GameObject()
{
    nw::Util::DebugCallerConstructor("GameObject");
}


nw::GameObject::~GameObject()
{
    nw::Util::DebugCallerDestructor("Drawable");
}