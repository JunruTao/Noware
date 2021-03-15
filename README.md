# Noware
A small C++ game/engine "Noware" development, using SFML as foundation graphics library.

----------------------------------------------------------------------
[comment]: <> (---------------------COMMENT START----------------------)
[comment]: <> (Format: Markdown format for better preview on GitHub.com)
[comment]: <> (----------------------COMMENT END-----------------------)

### Content Menu
* [1. Build Environment](#1-build-environment)
  * [1.1 Package](#11-package)
  * [1.2 build instruction](#12-build-instruction)
  * [1.3* Handy Windows custom doskey for build shortcuts](#13-handy-windows-custom-doskey-for-build-shortcuts)
* [2. File Structure](#2-file-structure)
  * [2.1 Master folder structure](#21-master-folder-structure)
  * [2.2 Source files structure](#22-source-files-structure)
* [3. Program Structure](#3-program-structure)
  * [Diagram #01:](#diagram-01)
  * [Diagram #02:](#diagram-02-relationship)



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
doskey cmaker=cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
doskey mm=mingw32-make
doskey mmi=mingw32-make install
```
|cmake debug  | cmake release | make| make install|
|:-----------:|:------------: |:---:| :---------: |
|    `cmaked` |  `cmaker`     | `mm`|    `mmi`    |

----------------------------------------------------------------------

## 2. File Structure

##### 2.1 Master folder structure:
- ![](.factory/ico/folder.png) - Noware
  - ![](.factory/ico/folder.png) - .factory
    - ![](.factory/ico/folder.png) - diagrams
    - ![](.factory/ico/folder.png) - ico
  - ![](.factory/ico/folder.png) - extern
    - ![](.factory/ico/folderE.png) - SFML
    - ![](.factory/ico/file.png) - `instructions.txt`
  - ![](.factory/ico/folder.png) - Noware <sup>(source files)</sup>
    - ![](.factory/ico/folder_n_files.png) ...<sup>&darr;(see Source files structure)</sup>
  - ![](.factory/ico/cmfile.png) - `CMakeLists.txt`
  - ![](.factory/ico/file.png) - `.gitignore`
  - ![](.factory/ico/file.png) - `LICENSE`
  - ![](.factory/ico/file.png) - `README.md`

##### 2.2 Source files structure:
- ![](.factory/ico/folder.png) - Noware <sup>(source files)</sup>
  - ![](.factory/ico/folderG.png) - config
    - ![](.factory/ico/file.png) - `config.env`
  - ![](.factory/ico/folderG.png) - fonts
    - ![](.factory/ico/file_m.png) ...
  - ![](.factory/ico/folderG.png) - images
    - ![](.factory/ico/file_m.png) ...
  - ![](.factory/ico/folder.png) - include
    - ![](.factory/ico/folder.png) - Noware
      - ![](.factory/ico/folder.png) - engine ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/folder.png) - graphics ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/folder.png) - util ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/file.png) - `engine.h`
      - ![](.factory/ico/file.png) - `graphics.h`
      - ![](.factory/ico/file.png) - `utility.h`
    - ![](.factory/ico/folder.png) - Noware_Game
      - ![](.factory/ico/folder.png) - game ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/file.png) - `game.h`
  - ![](.factory/ico/folder.png) - src
    - ![](.factory/ico/file.png) - `creator.cpp` &larr; (Entry Point)
    - ![](.factory/ico/folder.png) - Noware
      - ![](.factory/ico/folder.png) - engine ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/folder.png) - graphics ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/folder.png) - util ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/file.png) - `engine.cpp`
      - ![](.factory/ico/file.png) - `graphics.cpp`
      - ![](.factory/ico/file.png) - `utility.cpp`
      - ![](.factory/ico/cmfile.png) - `CMakeLists.txt`
    - ![](.factory/ico/folder.png) - Noware_Game
      - ![](.factory/ico/folder.png) - game ( ![](.factory/ico/file_m.png) ... )
      - ![](.factory/ico/file.png) - `game.cpp`
      - ![](.factory/ico/cmfile.png) - `CMakeLists.txt`
  - ![](.factory/ico/cmfile.png) - `CMakeLists.txt`

----------------------------------------------------------------------

## 3. Program Structure
##### Diagram #01:

![diagram01](.factory/diagrams/20200310_dgrm_architecture_v0001.png)





##### Diagram #02 Relationship:

![diagram01](.factory/diagrams/20200315_dgrm_header_relationship_v0001.png)






----------------------------------------------------------------------
[comment]: <> (---------------------COMMENT START----------------------)
[comment]: <> (            End of README Markdown File                 )
[comment]: <> (----------------------COMMENT END-----------------------)

[<p align="center"> ____ &uarr; Go back to Top &uarr; ____</p>](#noware) 

----------------------------------------------------------------------