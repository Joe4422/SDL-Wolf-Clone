#ifndef DATA_H_
#define DATA_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

/******************************************************************************
 * Typedefs
 *****************************************************************************/
struct point
{
	uint16_t	X;
	uint16_t	Y;
};
typedef struct point WORLD_POINT, MAP_POINT, SCREEN_POINT;

#endif