
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
	camera.x = 300;
	camera.y = 200;
	camera.z = 1000;
	camera.p = 0;
	camera.h = 0;
	camera.nearZ = 1.0f;
	camera.farZ = 5000000;
	use_3d = false;
	is_done = false;
	is_won = false;
}
RenderMaze::RenderMaze(const int w, const int h, const int f)
{
    //CleanUp();
	RenderMaze();
    initialize(w, h, f);
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
    M.PrintToTerminal();
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
void RenderMaze::Draw3DMap(void)
{
	// 3D version of the same maze
	int r, g, b, a, side;
	side = 50;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			switch (M.getMapPixel(x, y)) //
			{
			case '0':
				//glColor3ub(255, 255, 255);
				r = 200;
				g = 200;
				b = 200;
				a = 50;
				height = 10;
				break;
			case '1':
				//glColor3ub(0, 0, 0);
				r = 100;
				g = 0;
				b = 0;
				a = 50;
				height = 70;
				break;
			}

			glBegin(GL_QUADS);

			glColor4ub(r, g, b, a);

			//Front
			glVertex3i(-side + scale*(x), -side + scale*(y), height);
			glVertex3i(side + scale*(x), -side + scale*(y), height);
			glVertex3i(side + scale*(x), side + scale*(y), height);
			glVertex3i(-side + scale*(x), side + scale*(y), height);

			r = (r + 15 > 255) ? r - 15 : r + 15;
			g = (g + 15 > 255) ? g - 15 : g + 15;
			b = (b + 15 > 255) ? b - 15 : b + 15;
			glColor4ub(r, g, b, a);

			//Back
			glVertex3i(-side + scale*(x), -side + scale*(y), -side);
			glVertex3i(side + scale*(x), -side + scale*(y), -side);
			glVertex3i(side + scale*(x), side + scale*(y), -side);
			glVertex3i(-side + scale*(x), side + scale*(y), -side);

			//Bottom
			glVertex3i(-side + scale*(x), -side + scale*(y), -side);
			glVertex3i(side + scale*(x), -side + scale*(y), -side);
			glVertex3i(side + scale*(x), -side + scale*(y), height);
			glVertex3i(-side + scale*(x), -side + scale*(y), height);

			//Top
			glVertex3i(-side + scale*(x), side + scale*(y), -side);
			glVertex3i(side + scale*(x), side + scale*(y), -side);
			glVertex3i(side + scale*(x), side + scale*(y), height);
			glVertex3i(-side + scale*(x), side + scale*(y), height);

			//Left
			glVertex3i(-side + scale*(x), -side + scale*(y), -side);
			glVertex3i(-side + scale*(x), side + scale*(y), -side);
			glVertex3i(-side + scale*(x), side + scale*(y), height);
			glVertex3i(-side + scale*(x), -side + scale*(y), height);

			//Right
			glVertex3i(side + scale*(x), -side + scale*(y), -side);
			glVertex3i(side + scale*(x), side + scale*(y), -side);
			glVertex3i(side + scale*(x), side + scale*(y), height);
			glVertex3i(side + scale*(x), -side + scale*(y), height);

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

	if (use_3d == true)
	{
		//
	}
	else
	{
		glVertex2i(scale*(x), scale*y);
		glVertex2i(scale*(x), scale*(y + 1));
		glVertex2i(scale*(x + 1), scale*(y + 1));
		glVertex2i(scale*(x + 1), scale*y);
		glEnd();
	}
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
	if (M.player.x == M.exit_loc.x && M.player.y == M.exit_loc.y)
	{
		is_done = true;
		is_won = true;
	}
	else
	{
		switch (direction)
		{
		case FSKEY_UP:
			M.moveUp();
			break;
		case FSKEY_DOWN:
			M.moveDown();
			break;
		case FSKEY_LEFT:
			M.moveLeft();
			break;
		case FSKEY_RIGHT:
			M.moveRight();
			break;
		case FSKEY_W:
			camera.p += PI / 180.0;
			break;
		case FSKEY_S:
			camera.p -= PI / 180.0;
			break;
		case FSKEY_A:
			camera.h += PI / 180.0;
			break;
		case FSKEY_D:
			camera.h -= PI / 180.0;
			break;
		case FSKEY_X:
			break;
		}
	}
}
void RenderMaze::Render(void)
{
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	glViewport(0, 0, wid, hei);

	// Set up 3D drawing
	camera.SetUpCameraProjection();
	camera.SetUpCameraTransformation();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);


	// 3D drawing from here
	use_3d = true;
	Draw3DMap();

	// Set up 2D drawing
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	// 2D drawing from here

	glShadeModel(GL_SMOOTH);
	glColor3ub(230, 25, 25);
	glRasterPos2d(600, 580);
	YsGlDrawFontBitmap10x14("The Maze v.0.0.1");

	//FsSwapBuffers();
}

