#ifndef GRAPHICS_H_
#define GRAPHICS_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

#include "data.h"
#include "error.h"
#include "game.h"

/******************************************************************************
 * Typedefs
 *****************************************************************************/
struct framebuffer_handle;
typedef struct framebuffer_handle FRAMEBUFFER_HANDLE;

/******************************************************************************
 * Function declarations
 *****************************************************************************/
MESSAGE	Graphics_Init
(
	FRAMEBUFFER_HANDLE **	handle
);

void	Graphics_DeInit(void);

void	Graphics_DrawFrame
(
	FRAMEBUFFER_HANDLE *	handle,
	GAME_DATA *				data
);


#endif