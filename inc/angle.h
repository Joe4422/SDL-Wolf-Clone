#ifndef ANGLE_H_
#define ANGLE_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef float ANGLE;

/******************************************************************************
 * Function definitions
 *****************************************************************************/
ANGLE	Angle_Normalise
(
	ANGLE	angle
);

ANGLE	Angle_Add
(
	ANGLE	a,
	ANGLE	b
);

ANGLE	Angle_Sub
(
	ANGLE	a,
	ANGLE	b
);

float	Angle_Sin
(
	ANGLE	angle
);

float	Angle_Cos
(
	ANGLE	angle
);

float	Angle_Tan
(
	ANGLE	angle
);

ANGLE	Angle_InvTan
(
	float	ft
);

#endif