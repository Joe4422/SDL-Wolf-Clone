// temporary, all of it
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"
#include "ray.h"
#include "game.h"
#include "graphics.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define FOV	(90)

int main(int argc, char* argv[])
{
	WALL_TYPE 		wt1[] = { STONE_BLUE, STONE_BLUE, STONE_BLUE, STONE_BLUE, STONE_BLUE, STONE_BLUE, STONE_BLUE, STONE_BLUE };
	WALL_TYPE 		wt2[] = { STONE_BLUE,       NONE,       NONE,       NONE,       NONE,       NONE,       NONE, STONE_BLUE };
	WALL_TYPE *	data[] =  { (WALL_TYPE *)wt1, (WALL_TYPE *)wt2, (WALL_TYPE *)wt2, (WALL_TYPE *)wt2, (WALL_TYPE *)wt2, (WALL_TYPE *)wt2, (WALL_TYPE *)wt2, (WALL_TYPE *)wt1 };
	MAP testMap = 
	{
		8,
		8,
		data,
		"test map"
	};
	PLAYER player = { 1, { WALL_WIDTH * 2, WALL_WIDTH * 2 }, 0};
	GAME_DATA game = { &testMap, &player };
	FRAMEBUFFER_HANDLE * fb;
	bool draw = true;

	Error_Handle(Graphics_Init(&fb));

	while (draw == true)
	{
		SDL_Event event;

		Graphics_DrawFrame(fb, &game);
		//player.angle = Angle_Add(player.angle, 1);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				draw = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_q:
						player.angle = Angle_Sub(player.angle, 10);
						break;
					case SDLK_e:
						player.angle = Angle_Add(player.angle, 10);
						break;
					case SDLK_w:
						player.pos.Y -= 10;
						break;
					case SDLK_s:
						player.pos.Y += 10;
						break;
					case SDLK_a:
						player.pos.X -= 10;
						break;
					case SDLK_d:
						player.pos.X += 10;
						break;
				}
			}
		}
	}

	// int i, j;
	// for (i = 0; i < 36; i++)
	// {
	// 	printf("\t");
	// 	for (j = 0; j < 10; j++)
	// 	{
	// 		printf("%f, ", tanf((i * 10 + j) * (M_PI / 180)));
	// 	}
	// 	printf("\n");
	// }

	return 0;
}