#include <SDL.h>
#include <iostream>
#include "common_parameters.h"


int win_width = WINDOW_WIDTH, win_height = WINDOW_HEIGHT;

void Color(int& cnt, SDL_Renderer* ren)
{
	if (cnt == 1) SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	if (cnt == 2) SDL_SetRenderDrawColor(ren, 255, 150, 0, 255);
	if (cnt == 3) SDL_SetRenderDrawColor(ren, 255, 240, 0, 255);
	if (cnt == 4) SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
	if (cnt == 5) SDL_SetRenderDrawColor(ren, 0, 230, 255, 255);
	if (cnt == 6) SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	if (cnt == 7) SDL_SetRenderDrawColor(ren, 128, 0, 128, 255);
}

void DrawingTarget(int& cnt, int mouse_x, int mouse_y, SDL_Renderer* ren)
{
	Color(cnt, ren);
	SDL_Rect target = { mouse_x, mouse_y, 100, 100 };
	SDL_RenderFillRect(ren, &target);
	SDL_RenderPresent(ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
}

bool Logvinov(SDL_Window* win, SDL_Renderer* ren)
{
	int mouse_x = 450;
	int mouse_y = 250;
	int cnt = 1;

	SDL_Event ev;
	bool isRunning = true;
	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;
	bool isNextColor = false;
	bool isPastColor = false;

	while (isRunning)
	{

		while (SDL_PollEvent(&ev))
		{

			switch (ev.type)
			{
			case SDL_QUIT:
				while (true) {
					SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
					SDL_PollEvent(&ev);
					SDL_RenderClear(ren);
					SDL_RenderPresent(ren);
					if (ev.type == SDL_QUIT || ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						isRunning = false;
						SDL_Quit();
						return 0;
					}
					else if (ev.type == SDL_KEYDOWN)
						break;
				}
				break;

			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					win_width = ev.window.data1;
					win_height = ev.window.data2;
				}
				break;

			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					while (true)
					{
						SDL_PollEvent(&ev);
						SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
						SDL_RenderClear(ren);
						SDL_RenderPresent(ren);
						if (ev.type == SDL_QUIT || (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE && ev.type == SDL_KEYDOWN))
						{
							isRunning = false;
							SDL_Quit();
							return 0;
						}
						else if (ev.type == SDL_KEYDOWN)
							break;
					}

					break;
				case SDL_SCANCODE_EQUALS:
					isNextColor = true;
					if (cnt < 7) cnt++;
					break;
				case SDL_SCANCODE_MINUS:
					isPastColor = true;
					if (cnt > 1) cnt--;
					break;
				case SDL_SCANCODE_UP:
					isUpPressed = true;
					break;
				case SDL_SCANCODE_DOWN:
					isDownPressed = true;
					break;
				case SDL_SCANCODE_RIGHT:
					isRightPressed = true;
					break;
				case SDL_SCANCODE_LEFT:
					isLeftPressed = true;
					break;

				}
				break;

			case SDL_KEYUP:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					isUpPressed = false;
					break;
				case SDL_SCANCODE_DOWN:
					isDownPressed = false;
					break;
				case SDL_SCANCODE_RIGHT:
					isRightPressed = false;
					break;
				case SDL_SCANCODE_LEFT:
					isLeftPressed = false;
					break;
				}
				break;
			}
		}

		if (isUpPressed && !isDownPressed)       mouse_y -= 10;
		if (!isUpPressed && isDownPressed)       mouse_y += 10;
		if (isRightPressed && !isLeftPressed)    mouse_x += 10;
		if (!isRightPressed && isLeftPressed)    mouse_x -= 10;
		if (mouse_x <= 0) mouse_x = 0;
		if (mouse_y <= 0) mouse_y = 0;
		if (mouse_x + 100 >= win_width) mouse_x = win_width - 100;
		if (mouse_y + 100 >= win_height) mouse_y = win_height - 100;

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
		SDL_RenderClear(ren);

		DrawingTarget(cnt, mouse_x, mouse_y, ren);

		SDL_RenderPresent(ren);
		SDL_Delay(16);
	}

	return 0;
}