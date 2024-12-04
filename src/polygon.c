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

#include "polygon.h"
#include "res.h"
#include <math.h>

// Function to draw a polygon on the screen
void draw_polygon(SDL_Surface* surface, Polygon polygon, Uint32 color) 
{
    // Get the min and max y-values of the polygon to determine the scanline range
    int minY = INT_MAX ;
    int maxY = INT_MIN;

    Edge* edgeTable = malloc(polygon.vertexCount * sizeof(Edge)); // Allocate space for edges

    int edgeCount = 0; // Number of edges in the polygon

    for (int i = 0; i < polygon.vertexCount; i++) // Build the edge table
    {
        Point p1 = polygon.vertices[i]; // Get the current vertex
        Point p2 = polygon.vertices[(i + 1) % polygon.vertexCount]; // Get the next vertex

        if (p1.y == p2.y) 
            continue; // Skip horizontal edges

        if (p1.y > p2.y) // Ensure p1.y < p2.y
        {        
            const Point temp = p1;
            p1 = p2;
            p2 = temp;
        }

        // Add edge to the edge table
        edgeTable[edgeCount] = (Edge){p1.x, p1.y, p2.x, p2.y, p1.x, (p2.x - p1.x) / (p2.y - p1.y)};
        edgeCount++;

        if (p1.y < minY) // Update min and max y-values
            minY = (int)p1.y;

        if (p2.y > maxY) // Update min and max y-values
            maxY = (int)p2.y;
    }

    Edge** activeEdges = malloc(edgeCount * sizeof(Edge*)); // Allocate space for active edges
    int activeCount = 0; // Number of active edges on the current

    for (int y = minY; y <= maxY; y++) // Scan through each scanline
    {
        for (int i = 0; i < activeCount; ) // Remove edges that are no longer active
        {
            if (y >= (int)activeEdges[i]->y2)  // Remove edge if y >= y2
            {        
                for (int j = i; j < activeCount - 1; j++) // Shift remaining elements left             
                    activeEdges[j] = activeEdges[j + 1];
        
                activeCount--;
            } 
            else 
                i++;
        }

        for (int i = 0; i < edgeCount; i++) // Add edges that start on this scanline
        {
            if ((int)edgeTable[i].y1 == y) // Add edge if y1 == y
                activeEdges[activeCount++] = &edgeTable[i];
        }

        for (int i = 0; i < activeCount - 1; i++)  // Sort active edges by currentX
        {
            for (int j = 0; j < activeCount - i - 1; j++) 
            {
                if (activeEdges[j]->currentX > activeEdges[j + 1]->currentX) // Swap edges if currentX is greater
                {
                    Edge* temp = activeEdges[j];
                    activeEdges[j] = activeEdges[j + 1];
                    activeEdges[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < activeCount; i += 2) // Fill pixels between pairs of intersections 
        {
            if (i + 1 < activeCount)  // Ensure there are two edges
            {
                // Get the x-coordinates of the intersections
                const int xStart = (int)(activeEdges[i]->currentX + 0.5f);
                const int xEnd = (int)(activeEdges[i + 1]->currentX + 0.5f);

                for (int x = xStart; x <= xEnd; x++) // Fill pixels between intersections
                    SetPixel(surface, x, y, color); 
            }
        }

        for (int i = 0; i < activeCount; i++) // Update currentX for all active edges     
            activeEdges[i]->currentX += activeEdges[i]->slopeInverse;
    }
    // Free allocated memory
    free(edgeTable);
    free(activeEdges);
}

// Function to rotate a polygon around the origin
void rotate_polygon(Polygon* polygon, float angleRadians, float deltaTime, Point center)
{
    const float adjustedAngle = angleRadians * (deltaTime * 100.0f); // Adjust angle to frame time

    // Calculate sin and cos of the angle
    const float cosAngle = cosf(adjustedAngle);
    const float sinAngle = sinf(adjustedAngle);

    for (int i = 0; i < polygon->vertexCount; i++) // Loop through vertices and apply rotation
    {
        // Translate to origin
        const float x = polygon->vertices[i].x - center.x;
        const float y = polygon->vertices[i].y - center.y;

        // Apply rotation
        const float rotatedX = x * cosAngle - y * sinAngle;
        const float rotatedY = x * sinAngle + y * cosAngle;

        // Translate back to the original center
        polygon->vertices[i].x = rotatedX + center.x;
        polygon->vertices[i].y = rotatedY + center.y;
    }
}