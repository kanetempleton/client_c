#!/bin/bash

cd gfx
cd text
gcc -c *.c
cd ..
cd state
cd login
gcc -c *.c
cd ..
cd game
cd cpanel
cd cstate
gcc -c *.c
cd ..
gcc -c *.c
cd ..
cd map
gcc -c *.c
cd ..
cd hud
cd menus
gcc -c *.c
cd ..
gcc -c *.c
cd ..
gcc -c *.c
cd entity
gcc -c *.c
cd ..
cd ..
cd ..
cd component
gcc -c *.c
cd ..
gcc -c *.c
cd ..

cd net
cd communication
gcc -c *.c
cd ..
gcc -c *.c
cd ..

cd util
gcc -c *.c
cd ..

gcc -c *.c

#dont forget to add new directories to this line to link them
#also add any new libraries here or gf your whole program
gcc -o main *.c gfx/*.c gfx/text/*.c gfx/state/game/*.c gfx/state/game/cpanel/*.c gfx/state/game/cpanel/cstate/*.c gfx/state/game/map/*.c gfx/state/game/hud/*.c gfx/state/game/hud/menus/*.c gfx/state/game/entity/*.c gfx/state/login/*.c gfx/component/*.c net/*.c net/communication/*.c util/*.c -lSDL2 -lSDL2_ttf -lSDL2_image
