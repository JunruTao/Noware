# Noware
A small C++ game/engine "Noware" development, using SFML as foundation graphics library.

----------------------------------------------------------------------
[comment]: <> (---------------------COMMENT START----------------------)
[comment]: <> (Format: Markdown format for better preview on GitHub.com)
[comment]: <> (----------------------COMMENT END-----------------------)

### 1. Build Environment
1. CMake, MinGW Makefiles(Windows), Makefiles(Linux)
2. SFML package (see `extern/instructions.txt`)

    #### 1.2 build instruction
    * windows:
        > `mkdir build` <br>
        > `cd build`
        * debug install
        > `cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..`<br>
        > `mingw32-make install`
        * release install  
        > `cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..`<br>
        > `mingw32-make install`
    * Linux:
        * N/A (not avaliable at the moment)

### 2. Program Structure
* Diagram: <div style="text-align: right"> - `Timestamp March 10th, 2020`</div>

<img src=".factory/diagrams/20200310_dgrm_architecture_v0001.png">