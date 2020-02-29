/******************************************************************************
 * Includes
 *****************************************************************************/
#include "fixedpoint.h"

#include <stdbool.h>
#include <stdlib.h>

/******************************************************************************
 * Defines
 *****************************************************************************/
#define POINT				5
#define SIGN_MASK			0b0111111111111111
#define POINT_MASK			0b1111111111100000

#define SQRT_LOOKUP_SIZE	207

/******************************************************************************
 * Local variables
 *****************************************************************************/
static FP	sqrtLookupTable[SQRT_LOOKUP_SIZE] =
{
	0x12C0, 0x12A0, 0x1280, 0x1260, 0x1240, 0x1220, 0x1200, 0x11E0, 0x11C0, 0x11A0, 0x1180, 0x1160, 0x1140, 0x1120, 0x1100, 0x10E0,
	0x10C0, 0x10A0, 0x1080, 0x1060, 0x1040, 0x1020, 0x1000, 0x0FE0, 0x0FC0, 0x0FA0, 0x0F80, 0x0F60, 0x0F40, 0x0F20, 0x0F00, 0x0EE0,
	0x0EC0, 0x0EA0, 0x0E80, 0x0E60, 0x0E40, 0x0E20, 0x0E00, 0x0DE0, 0x0DC0, 0x0DA0, 0x0D80, 0x0D60, 0x0D40, 0x0D20, 0x0D00, 0x0CE0,
	0x0CC0, 0x0CA0, 0x0C80, 0x0C60, 0x0C40, 0x0C20, 0x0C00, 0x0BE0, 0x0BC0, 0x0BA0, 0x0B80, 0x0B60, 0x0B40, 0x0B20, 0x0B00, 0x0AE0,
	0x0AC0, 0x0AA0, 0x0A80, 0x0A60, 0x0A40, 0x0A20, 0x0A00, 0x09E0, 0x09C0, 0x09A0, 0x0980, 0x0960, 0x0940, 0x0920, 0x0900, 0x08E0,
	0x08C0, 0x08A0, 0x0880, 0x0860, 0x0840, 0x0820, 0x0800, 0x07E0, 0x07C0, 0x07A0, 0x0780, 0x0760, 0x0740, 0x0720, 0x0700, 0x06E0,
	0x06C0, 0x06A0, 0x0680, 0x0660, 0x0640, 0x0620, 0x0600, 0x05E0, 0x05C0, 0x05A0, 0x0580, 0x0560, 0x0540, 0x0520, 0x0500, 0x04E0,
	0x04C0, 0x04A0, 0x0480, 0x0460, 0x0440, 0x0420, 0x0400, 0x03E1, 0x03C1, 0x03A1, 0x0381, 0x0361, 0x0341, 0x0321, 0x0301, 0x02E1,
	0x02C1, 0x02A1, 0x0281, 0x0261, 0x0241, 0x0221, 0x0201, 0x01E1, 0x01C1, 0x01A1, 0x0181, 0x0161, 0x0142, 0x0122, 0x0102, 0x00E2,
	0x00C3, 0x00A3, 0x0084, 0x0065, 0x0048, 0x002D, 0x0020, 0x002D, 0x0048, 0x0065, 0x0084, 0x00A3, 0x00C3, 0x00E2, 0x0102, 0x0122,
	0x0142, 0x0161, 0x0181, 0x01A1, 0x01C1, 0x01E1, 0x0201, 0x0221, 0x0241, 0x0261, 0x0281, 0x02A1, 0x02C1, 0x02E1, 0x0301, 0x0321,
	0x0341, 0x0361, 0x0381, 0x03A1, 0x03C1, 0x03E1, 0x0400, 0x0420, 0x0440, 0x0460, 0x0480, 0x04A0, 0x04C0, 0x04E0, 0x0500, 0x0520,
	0x0540, 0x0560, 0x0580, 0x05A0, 0x05C0, 0x05E0, 0x0600, 0x0620, 0x0640, 0x0660, 0x0680, 0x06A0, 0x06C0, 0x06E0, 0x0700
};

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
	FP	out_fp = (abs(val) & ((POINT_MASK & SIGN_MASK) >> POINT)) << POINT;

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

FP	FP_Neg
(
	FP	fp
)
{
	return fp ^ ~SIGN_MASK;	
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

FP	FP_Sqrt
(
	FP	fp
)
{
	if (FP_IsNegative(fp) || fp >= FP_FromInt(SQRT_LOOKUP_SIZE))
	{
		return FP_FromInt(0);
	}
	else
	{
		return sqrtLookupTable[FP_ToInt(fp)];
	}
	
}

static bool	FP_IsNegative
(
	FP	fp
)
{
	return (bool)(fp & ~SIGN_MASK);
}