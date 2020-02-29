/******************************************************************************
 * Includes
 *****************************************************************************/
#include "ray.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define RAY_MAX_STEPS	256

/******************************************************************************
 * Function declarations
 *****************************************************************************/
FP	Ray_CalculateSlope
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
	FP			slope;
	uint16_t	i;

	// Null check on arguments
	if (!map || !player || !ray)
	{
		return;
	}

	slope = Ray_CalculateSlope(angle);

	if (FP_Compare(slope, FP_FromInt(1)) <= 0)
	{
		ray->dx = FP_FromInt(1);
		ray->dy = slope;
	}
	else
	{
		ray->dx = FP_Div(FP_FromInt(1), slope);
		ray->dy = FP_FromInt(1);
	}

	// Approximate pythagorean theorem
	if (FP_Abs(ray->dx) >= FP_Abs(ray->dy))
	{
		// ((7/8) * ray->dx) + (ray->dy / 2)
		ray->distEachInc = FP_Add(FP_Mul(FP_Div(FP_FromInt(7), FP_FromInt(8)), ray->dx), FP_Div(ray->dy, FP_FromInt(2)));
	}
	else
	{
		// ((7/8) * ray->dy) + (ray->dx / 2)
		ray->distEachInc = FP_Add(FP_Mul(FP_Div(FP_FromInt(7), FP_FromInt(8)), ray->dy), FP_Div(ray->dx, FP_FromInt(2)));
	}

	ray->start = player->pos;
	ray->distance = 0;
	ray->offsetX = 0;
	ray->offsetY = 0;

	for (i = 0; i < RAY_MAX_STEPS; i++)
	{
		WORLD_POINT	currentPos = { ray->start.X + FP_ToInt(ray->offsetX), ray->start.Y + FP_ToInt(ray->offsetY) };
		MAP_POINT	currentMapPos = { currentPos.X / WALL_LENGTH, currentPos.Y / WALL_LENGTH };
		WALL_TYPE	currentMapPosWallType = Map_GetWallType(map, &currentMapPos);

		if (currentMapPosWallType != NONE)
		{
			ray->hitWallType = currentMapPosWallType;
			return;
		}
		else
		{
			ray->distance = FP_Add(ray->distance, ray->distEachInc);
			ray->offsetX = FP_Add(ray->offsetX, ray->dx);
			ray->offsetY = FP_Add(ray->offsetY, ray->dy);
		}
	}
	ray->hitWallType = NONE;
	ray->distance = 0;
	return;
}

FP	Ray_CalculateSlope
(
	ANGLE	angle
)
{
	return Angle_Tan(angle);
}