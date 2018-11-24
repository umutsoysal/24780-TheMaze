//
//  rendermaze.cpp
//  PROJECTNEWTRIAL
//
//  Created by usoysal on 11/23/18.
//  Copyright © 2018 usoysal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "rendermaze.h"

RenderMaze::RenderMaze(void)
{
    width = 0;
    height = 0;
    scale = 0;
}
RenderMaze::RenderMaze(const int w, const int h, const int f)
{
    //CleanUp();
    width = w;
    height = h;
    scale = f;
    initialize();
}
void RenderMaze::initialize(const int w, const int h, const int f)
{
    //CleanUp();
    width = w;
    height = h;
    scale = f;
    initialize();
}
void RenderMaze::initialize(void)
{
    M.CleanUp();
    if (M.initialize(width, height))
    {
        fprintf(stderr, "RenderMaze->Draw: out of memory!\n");
        exit(1);
    }
    M.generate();
    //M.PrintToTerminal();
}
void RenderMaze::CleanUp(void)
{
    width = 0;
    height = 0;
    scale = 0;
    M.CleanUp();
}
RenderMaze::~RenderMaze(void)
{
    CleanUp();
}
void RenderMaze::DrawMap(void)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            switch (M.getMapPixel(x, y))
            {
                case '0':
                glColor3ub(255, 255, 255);
                break;
                case '1':
                glColor3ub(0, 0, 0);
                break;
                case 'O':
                glColor3ub(0, 0, 255);
                break;
                case 'X':
                glColor3ub(0, 255, 0);
                break;
                case '*':
                glColor3ub(255, 0, 0);
                break;
            }
            glBegin(GL_QUADS);
            
            glVertex2i(scale*(x), scale*y);
            glVertex2i(scale*(x), scale*(y + 1));
            glVertex2i(scale*(x + 1), scale*(y + 1));
            glVertex2i(scale*(x + 1), scale*y);
            glEnd();
        }
    }
}
void RenderMaze::DrawPlayer(void)
{
    int x = M.player.x;
    int y = M.player.y;
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    
    glVertex2i(scale*(x), scale*y);
    glVertex2i(scale*(x), scale*(y + 1));
    glVertex2i(scale*(x + 1), scale*(y + 1));
    glVertex2i(scale*(x + 1), scale*y);
    glEnd();
    
}
void RenderMaze::MovePlayer(const char direction)
{
    switch (direction)
    {
        case 'C':
        M.moveUp();
        break;
        case 'D':
        M.moveDown();
        break;
        case 'E':
        M.moveLeft();
        break;
        case 'F':
        M.moveRight();
        break;
    }
}

