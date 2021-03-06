# copyright Junru Tao
### Project  < Noware > Game/Engine-2021
### Make the main excutable
#------------------------------------#
#    Noware/[src] LEVEL CMakeList    #
#------------------------------------#

# Internal Include Directory
include_directories(${Noware_SOURCE_DIR}/Noware/include)
# External Include Directory
include_directories(${Noware_SOURCE_DIR}/extern/SFML/include)

set(NOWARE_CREATOR
    src/creator.cpp
)

# Main executable
add_executable(noware ${NOWARE_CREATOR})
add_subdirectory(src/Noware)
add_subdirectory(src/Noware_Game)

# Set installation path :def[ ${NOWARE_INSTALL_DIR} ]
if (CMAKE_BUILD_TYPE MATCHES Release)
    set(NOWARE_INSTALL_DIR ${Noware_SOURCE_DIR}/Noware-${NOWARE_VERSION})
else()
    set(NOWARE_INSTALL_DIR ${Noware_SOURCE_DIR}/Noware-d-${NOWARE_VERSION})
    # setting the debug flag by force as long as it is not release mode
    add_definitions(-DDEBUG)
endif()


# Install the main dependency
install(TARGETS noware DESTINATION ${NOWARE_INSTALL_DIR})

if(WIN32)
    if(EXPORT_RUNTIME)
    # [TODO] Change it to a proper installation fashion
    # Copy all the runtime dependencies from SFML
        # DEBUG MODE
        install(FILES
        ${Noware_SOURCE_DIR}/extern/SFML/bin/openal32.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-audio-d-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-graphics-d-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-network-d-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-system-d-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-window-d-2.dll
        CONFIGURATIONS DEBUG
        DESTINATION ${NOWARE_INSTALL_DIR})
        #RELEASE MODE
        install(FILES
        ${Noware_SOURCE_DIR}/extern/SFML/bin/openal32.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-audio-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-graphics-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-network-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-system-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-window-2.dll
        CONFIGURATIONS RELEASE
        DESTINATION ${NOWARE_INSTALL_DIR})
    endif(EXPORT_RUNTIME)
endif(WIN32)

install(DIRECTORY 
        ${Noware_SOURCE_DIR}/Noware/config
        DESTINATION ${NOWARE_INSTALL_DIR})
install(DIRECTORY 
        ${Noware_SOURCE_DIR}/Noware/fonts
        DESTINATION ${NOWARE_INSTALL_DIR})
install(DIRECTORY 
        ${Noware_SOURCE_DIR}/Noware/images
        DESTINATION ${NOWARE_INSTALL_DIR})