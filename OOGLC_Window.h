#pragma once 
#include "OOGLC_Game.h"
#include "glad.h"


enum GLColorBuffer {
	Color = GL_COLOR_BUFFER_BIT,
	Depth = GL_DEPTH_BUFFER_BIT,
	Stencil = GL_STENCIL_BUFFER_BIT,
	ClearScreen = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
};


//act on game.window
//struct Game game 

void clear_game_screen()
{
	glClear(ClearScreen);
}
