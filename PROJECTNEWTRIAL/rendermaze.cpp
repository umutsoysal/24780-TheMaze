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
#include "ysglfontdata.h"







RenderMaze::RenderMaze(void)
{
    width = 0;
    height = 0;
    scale = 0;
	is_done = false;
	is_won = false;
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
	is_done = false;
	is_won = false;
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
void RenderMaze::DrawPixel(const Node element, const int colors[3])
{
	int x = element.x;
	int y = element.y;
	glColor3ub(colors[0], colors[1], colors[2]);
	glBegin(GL_QUADS);

	glVertex2i(scale*(x), scale*y);
	glVertex2i(scale*(x), scale*(y + 1));
	glVertex2i(scale*(x + 1), scale*(y + 1));
	glVertex2i(scale*(x + 1), scale*y);
	glEnd();
}
void RenderMaze::DrawPlayer(void)
{
	int player_color[3] = { 255, 0 ,0 };
	int entry_color[3] = { 0, 150 ,150 };
	int exit_color[3] = { 0, 240 ,0 };

	DrawPixel(M.player, player_color);
	DrawPixel(M.entry_loc, entry_color);
	DrawPixel(M.exit_loc, exit_color);
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
	if (M.player.x == M.exit_loc.x && M.player.y == M.exit_loc.y)
	{
		is_done == true;
		is_won == true;
	}
}

