# copyright Junru Tao
### Project  < Noware > Game/Engine-2021
### Engine Files
#----------------------------------------------#
#       Noware/src/Noware LEVEL CMakeList      #
#----------------------------------------------#

# Internal Include Directory
include_directories(${Noware_SOURCE_DIR}/Noware/include)
# External Include Directory
include_directories(${Noware_SOURCE_DIR}/extern/SFML/include)


set(NOWARE_SRC 
    engine.cpp
        engine/main_loop.cpp
        engine/map.cpp
        engine/map_tile.cpp
        engine/game_object.cpp

    graphics.cpp
        graphics/window.cpp
        graphics/drawable.cpp
    
    utility.cpp
        util/configure.cpp
        util/system_helper.cpp
        util/io_font_manager.cpp
)

target_sources(noware PRIVATE ${NOWARE_SRC})