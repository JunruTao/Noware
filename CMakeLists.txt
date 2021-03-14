# copyright Junru Tao
# Project  < Noware > Game/Engine-2021

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 11)

project(Noware)

# Global Settings
set(EXPORT_RUNTIME true) # if Exporting Runtime dependencies
set(NOWARE_VERSION 1.0.0)
# source file directory
add_subdirectory(Noware)
# Passing Variables
get_directory_property(NOWARE_VERSION DIRECTORY Noware VARIABLES NOWARE_VERSION)


# Package Find and link: SFML
set(SFML_DIR "extern/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(noware sfml-system sfml-window sfml-graphics sfml-network sfml-audio)


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