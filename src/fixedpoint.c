/******************************************************************************
 * Includes
 *****************************************************************************/
#include "fixedpoint.h"

#include <stdbool.h>
#include <stdlib.h>

/******************************************************************************
 * Defines
 *****************************************************************************/
#define POINT		5
#define SIGN_MASK	0b0111111111111111
#define POINT_MASK	0b1111111111100000

/******************************************************************************
 * Function declarations
 *****************************************************************************/
static bool	FP_IsNegative
(
	FP	fp
);

/******************************************************************************
 * Function definitions
 *****************************************************************************/
int16_t	FP_ToInt
(
	FP	fp
)
{
	int16_t out = (fp & SIGN_MASK) >> POINT;

	if (FP_IsNegative(fp))
	{
		out = -out;
	}

	return out;
}

FP	FP_FromInt
(
	int16_t	val
)
{
	FP	out_fp = abs(val & ((POINT_MASK & SIGN_MASK) >> POINT)) << POINT;

	if (val < 0)
	{
		out_fp |= ~SIGN_MASK;
	}

	return out_fp;
}

FP	FP_Add
(
	FP	a,
	FP	b
)
{
	int16_t	_a, _b;
	int16_t	result_int;
	FP		result_fp;

	_a = a & SIGN_MASK;
	_b = b & SIGN_MASK;

	if (FP_IsNegative(a))
	{
		_a = -_a;
	}
	if (FP_IsNegative(b))
	{
		_b = -_b;
	}

	result_int = _a + _b;

	result_fp = (uint16_t)abs(result_int) & SIGN_MASK;

	if (result_int < 0)
	{
		result_fp |= ~SIGN_MASK;
	}

	return result_fp;
}

FP	FP_Sub
(
	FP	a,
	FP	b
)
{
	return FP_Add(a, b | ~SIGN_MASK);
}

FP	FP_Mul
(
	FP	a,
	FP	b
)
{
	int16_t	_a, _b;
	int16_t	result_int;
	FP		result_fp;

	_a = a & SIGN_MASK;
	_b = b & SIGN_MASK;

	if (FP_IsNegative(a))
	{
		_a = -_a;
	}
	if (FP_IsNegative(b))
	{
		_b = -_b;
	}

	result_int = (_a * _b) / (1 << POINT);

	result_fp = (uint16_t)abs(result_int) & SIGN_MASK;

	if (result_int < 0)
	{
		result_fp |= ~SIGN_MASK;
	}

	return result_fp;
}

FP	FP_Div
(
	FP	a,
	FP	b
)
{
	int16_t	_a, _b;
	int16_t	result_int;
	FP		result_fp;

	_a = a & SIGN_MASK;
	_b = b & SIGN_MASK;

	if (FP_IsNegative(a))
	{
		_a = -_a;
	}
	if (FP_IsNegative(b))
	{
		_b = -_b;
	}

	result_int = (_a * (1 << POINT)) / _b;

	result_fp = (uint16_t)abs(result_int) & SIGN_MASK;

	if (result_int < 0)
	{
		result_fp |= ~SIGN_MASK;
	}

	return result_fp;
}

int8_t	FP_Compare
(
	FP	a,
	FP	b
)
{
	int16_t _a = FP_ToInt(a);
	int16_t _b = FP_ToInt(b);

	if (_a < _b)
	{
		return -1;
	}
	else if (_a > _b)
	{
		return 1;
	}
	else
	{
		uint8_t aDec = (uint8_t)(a & ~POINT_MASK);
		uint8_t bDec = (uint8_t)(b & ~POINT_MASK);
		if (aDec < bDec)
		{
			return -1;
		}
		else if (aDec > bDec)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

FP	FP_Abs
(
	FP	fp
)
{
	return fp & SIGN_MASK;
}

static bool	FP_IsNegative
(
	FP	fp
)
{
	return (bool)(fp & ~SIGN_MASK);
}