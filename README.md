# Noware
A small C++ game/engine "Noware" development, using SFML as foundation graphics library.

----------------------------------------------------------------------
[comment]: <> (---------------------COMMENT START----------------------)
[comment]: <> (Format: Markdown format for better preview on GitHub.com)
[comment]: <> (----------------------COMMENT END-----------------------)

[Build Environment](#1.-build-environment)
[Package](#1.1-package)

----------------------------------------------------------------------
## 1. Build Environment
##### 1.1 Package
1. CMake, MinGW Makefiles(Windows), Makefiles(Linux)
2. SFML package (see `extern/instructions.txt`)

##### 1.2 build instruction
* windows:
    > `mkdir build`
    
    > `cd build`
    * debug install
    > `cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..`
    
    > `mingw32-make install`
    * release install  
    > `cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..`
    
    > `mingw32-make install`
* Linux:
    * N/A (not avaliable at the moment)

##### 1.3* Handy Windows custom `doskey` for build shortcuts
Content of `cmds.bat`
```
@echo off
:: MinGW and CMake Makefile shortcuts
doskey cmaked=cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
doskey cmaked=cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
doskey cmaker=mingw32-make
doskey mmi=mingw32-make install
```
|cmake debug  | cmake release | make| make install|
|:-----------:|:------------: |:---:| :---------: |
|    `cmaked` |  `cmaker`     | `mm`|    `mmi`    |

----------------------------------------------------------------------

## 2. File Structure

##### 2.1 Master folder structure:
- <img src=".factory/icons/folder_12x12.png"> - Noware
  - <img src=".factory/icons/folder_12x12.png"> - .factory
    - <img src=".factory/icons/folder_12x12.png"> - diagrams
    - <img src=".factory/icons/folder_12x12.png"> - icons
  - <img src=".factory/icons/folder_12x12.png"> - extern
    - <img src=".factory/icons/folderE_12x12.png"> - SFML
    - <img src=".factory/icons/file_12x12.png"> - `instructions.txt`
  - <img src=".factory/icons/folder_12x12.png"> - Noware <sup>(source files)</sup>
    - <img src=".factory/icons/folder_n_files_12x12.png"> ...<sup>&darr;(see Source files structure)</sup>
  - <img src=".factory/icons/cmfile_12x12.png"> - `CMakeLists.txt`
  - <img src=".factory/icons/file_12x12.png"> - `.gitignore`
  - <img src=".factory/icons/file_12x12.png"> - `LICENSE`
  - <img src=".factory/icons/file_12x12.png"> - `README.md`

##### 2.2 Source files structure:
- <img src=".factory/icons/folderG_12x12.png"> - Noware <sup>(source files)</sup>
  - <img src=".factory/icons/folderG_12x12.png"> - config
    - <img src=".factory/icons/file_12x12.png"> - `config.env`
  - <img src=".factory/icons/folderG_12x12.png"> - fonts
    - <img src=".factory/icons/file_m_12x12.png"> ...
  - <img src=".factory/icons/folderG_12x12.png"> - images
    - <img src=".factory/icons/file_m_12x12.png"> ...
  - <img src=".factory/icons/folder_12x12.png"> - include
    - <img src=".factory/icons/folder_12x12.png"> - Noware
      - <img src=".factory/icons/folder_12x12.png"> - engine
      - <img src=".factory/icons/folder_12x12.png"> - graphics
      - <img src=".factory/icons/folder_12x12.png"> - util
    - <img src=".factory/icons/folder_12x12.png"> - Noware_Game
      - <img src=".factory/icons/folder_12x12.png"> - game
  - <img src=".factory/icons/folder_12x12.png"> - src
    - <img src=".factory/icons/file_12x12.png"> - `creator.cpp` &larr; (Entry Point)
    - <img src=".factory/icons/folder_12x12.png"> - Noware
      - <img src=".factory/icons/folder_12x12.png"> - engine
      - <img src=".factory/icons/folder_12x12.png"> - graphics
      - <img src=".factory/icons/folder_12x12.png"> - util
      - <img src=".factory/icons/cmfile_12x12.png"> - `CMakeLists.txt`
    - <img src=".factory/icons/folder_12x12.png"> - Noware_Game
      - <img src=".factory/icons/folder_12x12.png"> - game
      - <img src=".factory/icons/cmfile_12x12.png"> - `CMakeLists.txt`
  - <img src=".factory/icons/cmfile_12x12.png"> - `CMakeLists.txt`

----------------------------------------------------------------------

## 3. Program Structure
##### Diagram <sup>#</sup>01:

<img align="center" width=500 src=".factory/diagrams/20200310_dgrm_architecture_v0001.png">