#include <SDL.h>
#include <iostream>
#include "common_parameters.h"

bool VladKuft(SDL_Window* win, SDL_Renderer* ren)
{

	SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);



	SDL_Rect rect = { 100, 100, 50, 50 };
	bool women = 0;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int deltaX;
	int deltaY;
	double distance;
	double speed = 5;
	bool to_you = 0, from_you = 0;
	while (1) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) 
			{
				while (true) {
					SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
					SDL_PollEvent(&ev);
					SDL_RenderClear(ren);
					SDL_RenderPresent(ren);
					if (ev.type == SDL_QUIT || ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						SDL_Quit();
						return 0;
					}
					else if (ev.type == SDL_KEYDOWN)
						break;
				}
			}
			else if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
				women = 1;
				to_you = 1;
			}
			else if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_LEFT) {
				women = 0;
				to_you = 0;
			}


			else if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_RIGHT) {
				women = 1;
				from_you = 1;
			}
			else if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_RIGHT) {
				women = 0;
				from_you = 0;
			}

			else if (ev.type == SDL_KEYDOWN && ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				while (true)
				{
					SDL_PollEvent(&ev);
					SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
					SDL_RenderClear(ren);
					SDL_RenderPresent(ren);
					if (ev.type == SDL_QUIT || (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE && ev.type == SDL_KEYDOWN))
					{
						SDL_Quit();
						return 0;
					}
					else if (ev.type == SDL_KEYDOWN)
						break;
				}
			}

		}

		if (women) {

			SDL_GetMouseState(&mouseX, &mouseY);
			deltaX = mouseX - rect.x - rect.w / 2;
			deltaY = mouseY - rect.y - rect.h / 2;
			distance = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (distance > speed) {
				if (to_you)
				{
					rect.x += deltaX * speed / distance;
					rect.y += deltaY * speed / distance;
				}
				if (from_you)
				{
					rect.x -= deltaX * speed / distance;
					rect.y -= deltaY * speed / distance;
				}
			}
			else {
				rect.x = mouseX - rect.w / 2;
				rect.y = mouseY - rect.h / 2;
			}
		}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRect(ren, &rect);

		SDL_RenderPresent(ren);
		SDL_Delay(16);
	}

	return 0;
}
