/******************************************************************************
 * Includes
 *****************************************************************************/
#include "ray.h"

#include <math.h>

/******************************************************************************
 * Defines
 *****************************************************************************/
#define RAY_MAX_STEPS	(256)

/******************************************************************************
 * Function declarations
 *****************************************************************************/
float	Ray_CalculateSlope
(
	ANGLE	angle
);

/******************************************************************************
 * Function definitions
 *****************************************************************************/
void	Ray_PerformRayCast
(
	MAP *		map,
	PLAYER *	player,
	RAY *		ray,
	ANGLE		angle
)
{
	float			slope;
	uint16_t	i;

	// Null check on arguments
	if (!map || !player || !ray)
	{
		return;
	}

	slope = Ray_CalculateSlope(angle);

	if (slope > 0)
	{
		if (slope <= 1.0f)
		{
			ray->dx = 1.0f;
			ray->dy = slope;
		}
		else
		{
			ray->dx = 1.0f / slope;
			ray->dy = 1.0f;
		}
	}
	else
	{
		if (slope >= -1.0f)
		{
			ray->dx = 1.0f;
			ray->dy = slope;
		}
		else
		{
			ray->dx = 1.0f / -slope;
			ray->dy = -1.0f;
		}
	}

	if (angle < 90 || angle > 270)
	{
		ray->dx = -ray->dx;
		ray->dy = -ray->dy;
	}

	ray->distEachInc = sqrtf(powf(ray->dx, 2) + powf(ray->dy, 2));

	ray->start = player->pos;
	ray->distance = 0;
	ray->offsetX = 0;
	ray->offsetY = 0;

	for (i = 0; i < RAY_MAX_STEPS; i++)
	{
		WORLD_POINT	currentPos = { ray->start.X + ray->offsetX, ray->start.Y + ray->offsetY };
		MAP_POINT	currentMapPos = { currentPos.X / WALL_WIDTH, currentPos.Y / WALL_WIDTH };
		WALL_TYPE	currentMapPosWallType = Map_GetWallType(map, &currentMapPos);

		if (currentMapPosWallType != NONE)
		{
			ray->hitWallType = currentMapPosWallType;
			if (currentPos.X % WALL_WIDTH == 0)
			{
				ray->xAligned = true;
			}
			else
			{
				ray->xAligned = false;
			}
			
			return;
		}
		else
		{
			ray->distance = ray->distance + ray->distEachInc;
			ray->offsetX = ray->offsetX + ray->dx;
			ray->offsetY = ray->offsetY + ray->dy;
		}
	}
	ray->hitWallType = NONE;
	ray->distance = 0;
	return;
}

float	Ray_CalculateSlope
(
	ANGLE	angle
)
{
	return Angle_Tan(angle);
}