#ifndef ANGLE_H_
#define ANGLE_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

#include "fixedpoint.h"

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef int16_t ANGLE;

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

FP	Angle_Sin
(
	ANGLE	angle
);

FP	Angle_Cos
(
	ANGLE	angle
);

FP	Angle_Tan
(
	ANGLE	angle
);

#endif