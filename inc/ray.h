#ifndef RAY_H_
#define RAY_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "data.h"
#include "map.h"
#include "player.h"

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef struct ray
{
	WORLD_POINT	start;
	float		offsetX;
	float		offsetY;
	float		dx;
	float		dy;
	float		distance;
	float		distEachInc;
	WALL_TYPE	hitWallType;
	bool		xAligned;
} RAY;

/******************************************************************************
 * Function declarations
 *****************************************************************************/
void	Ray_PerformRayCast
(
	MAP *		map,
	PLAYER *	player,
	RAY *		ray,
	ANGLE		angle
);

#endif