// temporary, all of it
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "fixedpoint.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "game.h"
#include "graphics.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define FOV	90

FP	floatToFP(float fl)
{
	FP out;
	float fl_abs;
	fl *= 32;
	fl = roundf(fl);
	if (fl < 0) fl_abs = -fl; else fl_abs = fl;
	out = (FP)fl_abs;
	out &= 0x7FFF;
	if (fl < 0) out |= 0x8000;
	return out;
}

int main(int argc, char* argv[])
{
	WALL_TYPE 		wt1[] = { STONE_BLUE, STONE_BLUE, STONE_BLUE, STONE_BLUE };
	WALL_TYPE 		wt2[] = { STONE_BLUE,       NONE,       NONE, STONE_BLUE };
	WALL_TYPE *	data[] =  { (WALL_TYPE *)wt1, (WALL_TYPE *)wt2, (WALL_TYPE *)wt2, (WALL_TYPE *)wt1 };
	MAP testMap = 
	{
		4,
		4,
		data,
		"test map"
	};
	PLAYER player = { 1, { WALL_LENGTH * 2, WALL_LENGTH * 2 }, 10};
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
						printf("ANGLE: %d\n", player.angle);
						break;
					case SDLK_e:
						player.angle = Angle_Add(player.angle, 10);
						printf("ANGLE: %d\n", player.angle);
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
	// for (i = 0; i < 13; i++)
	// {
	// 	printf("\t");
	// 	for (j = 0; j < 16; j++)
	// 	{
	// 		printf("0x%04X, ", floatToFP(sqrtf(powf((i * 16 + j) - 150, 2) + 1.0f)));
	// 	}
	// 	printf("\n");
	// }

	// for (i = 0; i < 360; i++)
	// {
	// 	if (Angle_Tan(i) == 0 || Angle_Tan(i) == 0x8000) continue;
	// 	printf("%d, ", FP_ToInt(FP_Div(1, Angle_Tan(i))));
	// }

	return 0;
}