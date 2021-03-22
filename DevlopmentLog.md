# Noware Development Log

###  2021/3/21

Successfully wrapped all the loops into `Engine`, and isolated `InitPlayground`, `ProcessEvents` and `DrawCalls` interface for `game.cpp`. After a few R&D, the current decision is to place **_Renderer_** global object for all the draw call access so that the drawables objects won't be storing `hRenderer` pointers all over the place. The down side is, you can only draw stuff on one window. But I think it works on this small game engine.

* **Main Goal**
Create a better API for Noware_Game, making all the calls user-friendly at a code level. At the same time making the game engine API flexible and robust.

* **Comments**
Standardazied most of the comments with a format so that making the headers more readable.

* **Data Pool**
Currently using a `nw::GeoPool::SFML` as demo, which stores a list of unique pointer resource of SFML drawables. The draw calls will just call another function to draw all the shapes. 

**TODO:**
place all the _data pools_ into a separate header at a very low level. so that the pushing and managements can be done internally. Maybe a good idea? still need to test it out.
