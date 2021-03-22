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

    graphics.cpp
        graphics/window.cpp
    
    utility.cpp
        util/configure.cpp
        util/system_helper.cpp
)

target_sources(noware PRIVATE ${NOWARE_SRC})