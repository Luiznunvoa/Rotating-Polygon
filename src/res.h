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

#ifndef RES_H
#define RES_H

#include <SDL.h>

typedef struct 
{
	SDL_Window *window;
	SDL_Surface *window_surface;

	SDL_Event event;

	Uint32 last_frame_time;
    Uint32 start_time;
    Uint32 frame_time;

    float delta_time;
} SDL_Instance;

int initSDL(SDL_Instance* instance);
void destroySDL(SDL_Instance* instance);
void SetPixel(SDL_Surface* surface, int x, int y, Uint32 color);
void getDeltaTime(SDL_Instance* instance);
void delayFrame(SDL_Instance* instance);

#endif // RES_H