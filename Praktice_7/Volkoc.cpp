#include <SDL.h>
#include <iostream>
#include "common_parameters.h"
#include <malloc.h>

bool Volkov(SDL_Window* win, SDL_Renderer* ren)
{
	static SDL_Event ev;
	static SDL_Point mousePosition;
	static int rectCount = 2;
	static SDL_Rect* rectArray = (SDL_Rect*)malloc(sizeof(SDL_Rect) * rectCount);
	static bool check = true;
	static bool pause = 0;

	if (check)
	{
		rectArray[0].x = 20;
		rectArray[0].y = 20;
		rectArray[0].w = 20;
		rectArray[0].h = 20;

		rectArray[1].x = 20;
		rectArray[1].y = 20;
		rectArray[1].w = 20;
		rectArray[1].h = 20;
		check = 0;
	}

	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);

	while (pause)
	{
		SDL_PollEvent(&ev);
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		SDL_RenderPresent(ren);
		if(ev.type == SDL_KEYDOWN)
			switch (ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				free(rectArray);
				return 0;
				break;
			
			default:
				pause = 0;
				break;
			}
		if (ev.type == SDL_QUIT)
		{
			free(rectArray);
			return 0;
			break;
		}
	}

	while (SDL_PollEvent(&ev))
	{

		switch (ev.type)
		{
		case SDL_QUIT:
			pause = 1;
			break;

		case SDL_KEYDOWN:
			switch (ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				pause = 1;
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (ev.button.button)
			{
			case SDL_BUTTON_LEFT:
				if (rectCount < 30)
				{
					rectCount++;
					rectArray = (SDL_Rect*)realloc(rectArray, sizeof(SDL_Rect) * rectCount);
				}
				break;
			case SDL_BUTTON_RIGHT:
				if (rectCount > 2)
				{
					rectCount--;
					rectArray = (SDL_Rect*)realloc(rectArray, sizeof(SDL_Rect) * rectCount);
				}
				break;
			}
			break;
		}
	}

	for (int i = rectCount-1;i > 0;i--)
	{
		rectArray[i] = rectArray[i - 1];
	}

	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	rectArray[0].x = mousePosition.x;
	rectArray[0].y = mousePosition.y;

	for (int i = 0, alpha = 255;i < rectCount;i++, alpha -= 255 / rectCount)
	{
		SDL_SetRenderDrawColor(ren, 255, 200, 150, alpha);
		SDL_RenderFillRect(ren, &rectArray[i]);
	}

	SDL_RenderPresent(ren);

	return 1;
}
