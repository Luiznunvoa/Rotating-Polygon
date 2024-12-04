//
// Copyright (c) 2024 Luiz Gabriel Moraes "Luiz".
//
// This file is part of Rotating-Polygon.
//
// Rotating-Polygon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3
// as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// Rotating-Polygon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>..
//

#include "res.h"

#define FPS 60

// Initialization of the window using SDL
int initSDL(SDL_Instance* instance)
{
    *instance = (SDL_Instance){0};

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL Initialization error: %s\n", SDL_GetError());
        return 0;
    }

    instance->window =  SDL_CreateWindow(
        "Geometry?",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 800,
        SDL_WINDOW_SHOWN
    );
    if (instance->window == NULL)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Window initialization error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    instance->window_surface = SDL_GetWindowSurface(instance->window);
    instance->last_frame_time = SDL_GetTicks();
    return 1;
}

// Destroy the window and quit SDL
void destroySDL(SDL_Instance* instance)
{
	SDL_DestroyWindow(instance->window);
	SDL_Quit();
}

// Set a pixel on the window surface
void SetPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
        return;

    Uint8* pixels = (Uint8*)surface->pixels;
    Uint8* target_pixel = pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    *(Uint32*)target_pixel = color;
}

// Get the delta time between frames
void getDeltaTime(SDL_Instance* instance)
{
    instance->start_time = SDL_GetTicks();
        instance->delta_time = (instance->start_time - instance->last_frame_time) / 1000.0f;

    if (instance->delta_time > (1.0f / FPS))
        instance->delta_time = 1.0f / FPS; 
}

// Delay the frame to control the FPS
void delayFrame(SDL_Instance* instance)
{
    instance->frame_time = SDL_GetTicks() - instance->start_time;

    if (instance->frame_time < (1000 / FPS)) // Control FPS
        SDL_Delay((1000 / FPS) - instance->frame_time);

    instance->last_frame_time = instance->start_time;
}