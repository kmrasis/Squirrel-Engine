# <p style="text-align:center;">Squirrel-Engine</p>
#### Game Engine build and managed currently(exclusively) for 
    OS      : Linux Mint 21.2
    Kernel  : 5.15.0-126-generic
    Arch    : x86_64 GNU/Linux

#### Pre Requisites / Dependencies
- cmake
- libwayland-dev
- libx11-dev
- libxandr-dev
- libxinerama-dev
- libxcursor-dev
- libxi-dev
- libxext-dev
- libxkbcommon-dev
- libgl1-mesa-dev
- mesa-common-dev

#### 3rd party libraries
    glfw      : Pre-compiled Version 3.4
    spdlog    : Pre-compiled Version 1.15.0


#### Build Method

- clone and enter git repo
    ```
    git clone git@github.com:kmrasis/Squirrel-Engine.git
    cd Squirrel-Engine
    ```

- make build directory and enter it
    ```
    mkdir build
    cd build
    ```

- run cmake to generate necessary config files
    ```
    cmake ..
    ```

- start building
    ```
    make
    ```

#### Executing the program

- After successfull build executable is generated at ardilla/ardilla
    ```
    ./ardilla/ardilla
    ```
    