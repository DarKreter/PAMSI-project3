`sudo apt update`

`sudo apt install libudev-dev libopenal-dev libvorbis-dev libflac++-dev xorg-dev libfreetype6-dev`

`git submodule update --init`


Example usage:

`mkdir build && cd build`

`cmake ..`

`cmake --build . --target firmware`

`./firmware/firmware`