# copyright Junru Tao
### Project  < Noware > Game/Engine-2021
### Engine Files
#----------------------------------------------#
#    Noware/src/Noware_Game LEVEL CMakeList    #
#----------------------------------------------#

# Internal Include Directory
include_directories(${Noware_SOURCE_DIR}/Noware/include)
# External Include Directory
include_directories(${Noware_SOURCE_DIR}/extern/SFML/include)


set(NOWARE_GAME_SRC 
    game.cpp
)

target_sources(noware PRIVATE ${NOWARE_GAME_SRC})