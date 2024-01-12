/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "GameBox.h"


int main(int argc, char* args[])
{
	GameBox g;
	if (!g.mainLoop())
		g.~GameBox();
	return 0;
}
