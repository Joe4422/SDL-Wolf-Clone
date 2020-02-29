/******************************************************************************
 * Includes
 *****************************************************************************/
#include "map.h"

#include <stddef.h>

/******************************************************************************
 * Function definitions
 *****************************************************************************/
MAP *	Map_Load
(
	char *	path
)
{
	return NULL;
}

WALL_TYPE	Map_GetWallType
(
	MAP *		map,
	MAP_POINT *	point
)
{
	if (point->X >= map->width || point->Y >= map->height)
	{
		return NONE;
	}

	return map->data[point->Y][point->X];
}