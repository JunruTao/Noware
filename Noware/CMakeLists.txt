
# Internal Include Directory
include_directories(${Noware_SOURCE_DIR}/Noware/include)
# External Include Directory
include_directories(${Noware_SOURCE_DIR}/extern/SFML/include)

set(NOWARE_SRC
    src/creator.cpp
)


# Main executable
add_executable(noware ${NOWARE_SRC})

# Set installation path
set(NOWARE_INSTALL_DIR ${Noware_SOURCE_DIR}/Noware${NOWARE_VERSION})

# Install the main dependency
install(TARGETS noware DESTINATION ${NOWARE_INSTALL_DIR}/bin)

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
        DESTINATION ${NOWARE_INSTALL_DIR}/bin)
        #RELEASE MODE
        install(FILES
        ${Noware_SOURCE_DIR}/extern/SFML/bin/openal32.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-audio-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-graphics-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-network-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-system-2.dll
        ${Noware_SOURCE_DIR}/extern/SFML/bin/sfml-window-2.dll
        CONFIGURATIONS RELEASE
        DESTINATION ${NOWARE_INSTALL_DIR}/bin)
    endif(EXPORT_RUNTIME)
endif(WIN32)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    message("debug mode")
endif(EXPORT_RUNTIME)