#include "Game.hpp"

int main(int argc, char *args[])
{
    Game game;
    game.Run();
    return 0;
}

/*
    REQUISITE KNOWLEDGE:
    1. Working with the SDL2 library.
    2. For general theory behind implementing a raycaster check these two tutorials:
    https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
    https://lodev.org/cgtutor/raycasting.html

    The raycasting algorithm implemented here for calculating the distance to the wall is explained in detail here:
    https://youtu.be/NbSee-XM7WA
    The theory behind the textured walls implementation is explained here:
    https://youtu.be/HEb2akswCcw
    For understanding the math behind the floor and ceiling casting I recommend reading this:
    https://wynnliam.github.io/raycaster/news/tutorial/2019/04/09/raycaster-part-03.html
*/