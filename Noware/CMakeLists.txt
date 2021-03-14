# copyright Junru Tao
### Project  < Noware > Game/Engine-2021
### Make the main excutable


# Internal Include Directory
include_directories(${Noware_SOURCE_DIR}/Noware/include)
# External Include Directory
include_directories(${Noware_SOURCE_DIR}/extern/SFML/include)

set(NOWARE_CREATOR
    src/creator.cpp
)

# Main executable
add_executable(noware ${NOWARE_CREATOR})

# Set installation path
if (CMAKE_CONFIGURATION_TYPES EQUAL "Debug")
    set(NOWARE_INSTALL_DIR ${Noware_SOURCE_DIR}/Noware-d-${NOWARE_VERSION})
elseif(CMAKE_CONFIGURATION_TYPES EQUAL "Release")
    set(NOWARE_INSTALL_DIR ${Noware_SOURCE_DIR}/Noware${NOWARE_VERSION})
endif()

# Install the main dependency
install(TARGETS noware DESTINATION ${NOWARE_INSTALL_DIR}/bin)