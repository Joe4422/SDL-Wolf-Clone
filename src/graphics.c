/***********************************************
 * Includes
 ***********************************************/
#include "graphics.h"

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "ray.h"

/***********************************************
 * Defines
 ***********************************************/
#define FRAMEBUFFER_WIDTH	(320)
#define FRAMEBUFFER_HEIGHT	(200)

#define FOV					(90.0f)
#define FOV_RAY_INCREMENT	(0.1f)
#define RAY_COUNT			(FOV / FOV_RAY_INCREMENT)
#define RAYS_PER_COLUMN		(RAY_COUNT / FRAMEBUFFER_WIDTH)

/***********************************************
 * Typedefs
 ***********************************************/
struct framebuffer_handle
{
	uint32_t *		framebuffer;
	SDL_Texture *	texture;
};

typedef struct color
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
} COLOR;

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
	int i;
	int j;
	SCREEN_POINT center = { FRAMEBUFFER_WIDTH / 2, FRAMEBUFFER_HEIGHT / 2 };
	float distToVplane;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (i = 0; i < FRAMEBUFFER_WIDTH; i++)
	{
		int16_t dy;
		float avgDist = 0;
		ANGLE localAngle;
		ANGLE worldAngle;
		ANGLE wallTopAngle;
		float tan;
		COLOR wallColor;
		
		RAY ray;

		for (j = 0; j < RAYS_PER_COLUMN; j++)
		{
			localAngle = Angle_Normalise(((i * RAYS_PER_COLUMN + j) * FOV_RAY_INCREMENT) - (FOV / 2));
			worldAngle = Angle_Add(localAngle, data->player->angle);

			Ray_PerformRayCast(data->currentMap, data->player, &ray, worldAngle);
			
			avgDist += ray.distance;
		}

		if (ray.hitWallType == NONE)
		{
			continue;
		}

		if (Angle_Sin(localAngle) != 0)
		{
			distToVplane = (i - (FRAMEBUFFER_WIDTH / 2)) / Angle_Sin(localAngle);
		}

		avgDist /= RAYS_PER_COLUMN;

		tan = ((float)WALL_HEIGHT / 2.0f) / avgDist;
		wallTopAngle = Angle_InvTan(tan);

		if (localAngle < Angle_Normalise(-45.0f) || localAngle > Angle_Normalise(45.0f))
		{
			dy = Angle_Tan(wallTopAngle) * distToVplane;
		}
		else
		{
			dy = (1 / Angle_Tan(wallTopAngle)) * distToVplane;
		}

		if (ray.xAligned)
		{
			wallColor.a = 255;
			wallColor.r = 0;
			wallColor.g = 0;
			wallColor.b = 224;
		}
		else
		{
			wallColor.a = 255;
			wallColor.r = 0;
			wallColor.g = 0;
			wallColor.b = 255;
		}
		
		
		SDL_SetRenderDrawColor(renderer, 95, 95, 95, 255);
		SDL_RenderDrawLine(renderer, i, 0, i, center.Y - dy - 1);
		SDL_SetRenderDrawColor(renderer, wallColor.r, wallColor.g, wallColor.b, wallColor.a);
		SDL_RenderDrawLine(renderer, i, center.Y - dy, i, center.Y + dy);
		SDL_SetRenderDrawColor(renderer, 159, 159, 159, 255);
		SDL_RenderDrawLine(renderer, i, center.Y + dy + 1, i, FRAMEBUFFER_HEIGHT - 1);
	}
	SDL_RenderPresent(renderer);
}