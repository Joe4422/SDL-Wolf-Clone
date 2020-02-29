// temporary, all of it

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
#include <unistd.h>

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

int main()
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
	PLAYER player = { 1, { WALL_LENGTH * 2, WALL_LENGTH * 2 }, 0};
	GAME_DATA game = { &testMap, &player };
	FRAMEBUFFER_HANDLE * fb;
	Graphics_Init(&fb);

	while (1)
	{
		Graphics_DrawFrame(fb, &game);
		player.angle = Angle_Add(player.angle, 1);
	}

	// for (i = 0; i < FOV; i++)
	// {
	// 	RAY ray;
	// 	Ray_PerformRayCast(&testMap, &player, &ray, Angle_Sub(player.angle, (ANGLE)(FOV / 2 + i)));

	// 	printf("%d, ", FP_ToInt(ray.distance));
	// }

	// int i, j;

	// for (i = 0; i < 36; i++)
	// {
	// 	printf("\t");
	// 	for (j = 0; j < 10; j++)
	// 	{
	// 		printf("0x%04X, ", floatToFP(tanf((float)(i * 10 + j) * (M_PI / 180.0f))));
	// 	}
	// 	printf("\n");
	// }

}