# copyright Junru Tao
### Project  < Noware > Game/Engine-2021
### Engine Files


# Internal Include Directory
include_directories(${Noware_SOURCE_DIR}/Noware/include)
# External Include Directory
include_directories(${Noware_SOURCE_DIR}/extern/SFML/include)


set(NOWARE_SRC 
    engine/engine.cpp
    graphics/graphics.cpp
    util/utility.cpp
)

target_sources(noware PRIVATE ${NOWARE_SRC})