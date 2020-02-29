#ifndef RAY_H_
#define RAY_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "data.h"
#include "fixedpoint.h"
#include "map.h"
#include "player.h"

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef struct ray
{
	WORLD_POINT	start;
	FP			offsetX;
	FP			offsetY;
	FP			dx;
	FP			dy;
	FP			distance;
	FP			distEachInc;
	WALL_TYPE	hitWallType;
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