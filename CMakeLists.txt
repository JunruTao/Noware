# copyright Junru Tao
# Project  < Noware > Game/Engine-2021
#------------------------------------#
#       TOP LEVEL CMakeList          #
#------------------------------------#
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

project(Noware)

# Global Settings
set(EXPORT_RUNTIME true) # if Exporting Runtime dependencies
set(NOWARE_VERSION 1.0.0)
# source file directory
add_subdirectory(Noware)
# Passing Variables
get_directory_property(NOWARE_VERSION DIRECTORY Noware VARIABLES NOWARE_VERSION)
get_directory_property(EXPORT_RUNTIME DIRECTORY Noware VARIABLES EXPORT_RUNTIME)


# Package Find and link: SFML
set(SFML_DIR "extern/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(noware sfml-system sfml-window sfml-graphics sfml-network sfml-audio)


