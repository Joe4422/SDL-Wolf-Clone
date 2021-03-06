#ifndef MAP_H_
#define MAP_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include "data.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define WALL_WIDTH	(32)
#define WALL_HEIGHT (32)

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef enum wall_type
{
	NONE,
	STONE_BLUE,
	STONE_GRAY
} WALL_TYPE;

typedef struct map
{
	uint16_t		width;
	uint16_t		height;
	WALL_TYPE **	data;
	char *			name;
} MAP;

/******************************************************************************
 * Function declarations
 *****************************************************************************/
MAP *	Map_Load
(
	char *	path
);

WALL_TYPE	Map_GetWallType
(
	MAP *		map,
	MAP_POINT *	point
);

#endif