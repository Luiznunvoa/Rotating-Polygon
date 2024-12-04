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

    /* Examples:
    
        ==SQUARE==
        {200, 200}, 
        {400, 200}, 
        {400, 400}, 
        {200, 400}  

        (200, 200)  0 ------- 0 (400, 200)  
                    |         |             
                    |         |             
                    |         |             
                    |         |            
        (200, 400)  0 ------- 0 (400, 400)  

        =TRIANGLE=
        {200, 200}, 
        {400, 200}, 
        {400, 400}

        (200, 200)  0 ------- 0 (400, 200)  
                     \        |             
                       \      |             
                         \    |            
                           \  |             
                             \0 (400, 400)  
    */

    Point points[] = 
    {
        {100, 300},
        {200, 200}, 
        {400, 200}, 
        {500, 300},
        {400, 400}, 
        {200, 400} 
    };
    Polygon polygon = {points, 6};

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
                case SDL_KEYDOWN:
                    if (instance.event.key.keysym.sym == SDLK_ESCAPE)
                        quit = 1;
                    break;
                default:
                    break;
            }
        }

        rotate_polygon(&polygon, M_PI / 180.0f, instance.delta_time, (Point){400, 400}); // Rotate around a point

        LOCK_SURFACE(instance.window_surface);

        SDL_FillRect(instance.window_surface, NULL, 0xFFFFFF); // Clear screen

        draw_polygon(instance.window_surface, polygon, 0x00FF00);

        UNLOCK_SURFACE(instance.window_surface);

        SDL_UpdateWindowSurface(instance.window);

        delayFrame(&instance);
    }
    destroySDL(&instance);
    return;
}