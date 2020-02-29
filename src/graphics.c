/***********************************************
 * Includes
 ***********************************************/
#include "graphics.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "ray.h"

/***********************************************
 * Defines
 ***********************************************/
#define FRAMEBUFFER_WIDTH	640
#define FRAMEBUFFER_HEIGHT	480

#define FOV					90

/***********************************************
 * Typedefs
 ***********************************************/
struct framebuffer_handle
{
	uint32_t *		framebuffer;
	SDL_Texture *	texture;
};

/***********************************************
 * Global variables
 ***********************************************/
static bool 			sdlInitComplete = false;
static SDL_Window *		window = NULL;
static SDL_Surface *	surface = NULL;
static SDL_Renderer *	renderer = NULL;

/***********************************************
 * Function declarations
 ***********************************************/

/***********************************************
 * Function definitions
 ***********************************************/
MESSAGE	Graphics_Init
(
	FRAMEBUFFER_HANDLE **	handle
)
{
	if (sdlInitComplete == false)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
        	THROW_ERROR(STATUS_FAILURE, "Could not initialise SDL!");
		}
	}

	if (window == NULL)
	{
    	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			THROW_ERROR(STATUS_FAILURE, "Could not create SDL window!");
		}
	}

	if (renderer == NULL)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			THROW_ERROR(STATUS_FAILURE, "Could not create SDL renderer!");
		}
	}

	if (surface == NULL)
	{
		surface = SDL_GetWindowSurface(window);
		if (surface == NULL)
		{
			THROW_ERROR(STATUS_FAILURE, "Could not get SDL window surface!");
		}
	}

	*handle = malloc(sizeof(FRAMEBUFFER_HANDLE));
	if (*handle == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer handle!");
	}

	(*handle)->framebuffer = malloc(FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT * sizeof(uint32_t));
	if ((*handle)->framebuffer == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer array!");
	}

	(*handle)->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	if ((*handle)->texture == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer texture!");
	}

	RETURN_STATUS_OK;
}

void	Graphics_DeInit(void)
{

}

void	Graphics_DrawFrame
(
	FRAMEBUFFER_HANDLE *	handle,
	GAME_DATA *				data
)
{
	// Quick and dirty
	int i, j;
	SCREEN_POINT center = { FRAMEBUFFER_WIDTH / 2, FRAMEBUFFER_HEIGHT / 2 };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	for (i = 0; i < FOV; i++)
	{
		RAY ray;
		int16_t dy;
		Ray_PerformRayCast(data->currentMap, data->player, &ray, Angle_Sub(data->player->angle, (ANGLE)(FOV / 2 + i)));

		dy = FP_ToInt(FP_Div(FP_FromInt(FRAMEBUFFER_HEIGHT), ray.distance)) / 2;

		for (j = FRAMEBUFFER_WIDTH / FOV * i; j < FRAMEBUFFER_WIDTH / FOV * (i + 1); j++)
		{
			SDL_RenderDrawLine(renderer, j, center.Y - dy, j, center.Y + dy);
		}
	}

	SDL_RenderPresent(renderer);
}