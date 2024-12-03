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

#ifndef POLYGON_H
#define POLYGON_H

#include <SDL.h>

typedef struct {
    float x1, y1, x2, y2;  // Endpoints of the edge
    float currentX;        // Current x-coordinate during scanning
    float slopeInverse;    // Inverse slope for edge stepping
} Edge;

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point *vertices;  // Array of vertices
    int vertexCount;  // Number of vertices
} Polygon;

void draw_polygon(SDL_Surface *surface, Polygon polygon, Uint32 color);
void rotate_polygon(Polygon *polygon, float angleRadians, Point center);

#endif // POLYGON_H