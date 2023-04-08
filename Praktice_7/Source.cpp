#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include "func.h"
#include <math.h>
#include "common_parameters.h"
#include "Logvinov.h"
#include "VadimSkor.h"
#include "VladKuft.h"
#include "Volkov.h"



SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surface = NULL;


void WindowDelay()
{
	static int time = 0;
	while (true)
	{
		if (clock() - time >= 1000 / FPS)
		{
			time = clock();
			break;
		}
		else
			SDL_Delay(1);
	}
}

int main(int argc, char* argv[])
{

	int exType = 0;
	SDL_KeyboardEvent keyBoardEvent;

	printf_s("\
1 - Block manipulation\n\
2 - Whack a mole\n\
3 - Rect slider\n\
4 - Mouse murder\n");

	while (true)
	{
		printf_s("Enter interaction type: ");
		scanf_s("%d", &exType);
		if (!(exType > 0 && exType <= 4))
			printf_s("Invalid type! Try again.\n");
		else
			break;
	}

	Init(&win, &ren, &win_surface, WINDOW_HEIGHT, WINDOW_WIDTH);

	switch (exType)
	{
	case 1:
		while (true)
		{
			if(!Logvinov(win, ren))
				break;
		}
		break;
	case 2:
		while (true)
		{
			if (!VadimSkor(win, ren))
				break;
		}
		break;
	case 3:
		while (true)
		{
			if (!Volkov(win, ren))
				break;
		}
		break;
	case 4:
		while (true)
		{
			if (!VladKuft(win, ren))
				break;
		}
		break;
	}

	DeInit(0, &win, &ren, &win_surface);
	
	return 0;
}