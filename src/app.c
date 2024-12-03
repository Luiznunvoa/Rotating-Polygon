//
// Copyright (c) 2024 Luiz Gabriel Moraes "Luiz".
//
// This file is part of SimpleChess_SDL.
//
// SimpleChess_SDL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3
// as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// SimpleChess_SDL is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>..
//

#include "app.h"
#include "res.h"
#include "polygon.h"

#define LOCK_SURFACE(surface) if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface)
#define UNLOCK_SURFACE(surface) if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface)

void app(void)
{
    SDL_Instance instance;

    if (!initSDL(&instance))
    {
        SDL_ShowSimpleMessageBox(16, "ERROR", "Failed to Initialize SDL", instance.window);
        destroySDL(&instance);
        return;
    }

    Point points[] = 
    {
        {200, 200}, // Top-left 
        {400, 200}, // Top-right 
        {300, 400}  // Bottom-right 
    };
    Polygon polygon = {points, 3};

    int quit = 0;
    while (!quit)
    {
        getDeltaTime(&instance);

        while (SDL_PollEvent(&instance.event))
        {
            switch (instance.event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                default:
                    break;
            }
        }

        rotate_polygon(&polygon, M_PI / 180.0f, (Point){400, 400}); // Rotate around the center of the screen

        LOCK_SURFACE(instance.window_surface);

        SDL_FillRect(instance.window_surface, NULL, 0xFFFFFF);

        draw_polygon(instance.window_surface, polygon, 0x00FF00);

        UNLOCK_SURFACE(instance.window_surface);

        SDL_UpdateWindowSurface(instance.window);

        delayFrame(&instance);
    }

    destroySDL(&instance);
    return;
}