#pragma once
#include <SDL.h>

bool Logvinov(SDL_Window* win, SDL_Renderer* ren);
void Color(int& cnt, SDL_Renderer* ren);
void DrawingTarget(int& cnt, int mouse_x, int mouse_y, SDL_Renderer* ren);