#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <time.h>
#include <string>
#include <sstream>
#include "fssimplewindow.h"
#include "rendermaze.h"
#include "ysglfontdata.h"
//#include "window.h" //NOT IMPLEMENTED

std::string to_string(double x) // This one is from the internet.
{
    std::ostringstream ss;
    ss << x;
    return ss.str();
}

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
    side = 50;
    time = 300;
    use_3d = false;
    is_done = false;
    is_won = false;
}
RenderMaze::RenderMaze(const int w, const int h, const int f, const int t, const int l)
{
    //CleanUp();
    RenderMaze();
    initialize(w, h, f, t, l);
}
void RenderMaze::initialize(const int w, const int h, const int f, const int t, const int l)
{
    //CleanUp();
    width = w;
    height = h;
    scale = f;
    time = t;
    level = l;
    camera.x = 300;
    camera.y = 200;
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
    timer_start(); // Starts the timer 
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
void RenderMaze::Draw3DMap(void)
{
    // 3D version of the same maze
    int r, g, b, a;
    side = scale/2;
    int col_height = 0;
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
                col_height = 10;
                break;
            case '1':
                //glColor3ub(0, 0, 0);
                r = 100;
                g = 0;
                b = 0;
                a = 50;
                col_height = 70;
                break;
            }

            glBegin(GL_QUADS);

            glColor4ub(r, g, b, a);

            //Front
            glVertex3i(-side + scale*(x), -side + scale*(y), col_height);
            glVertex3i(side + scale*(x), -side + scale*(y), col_height);
            glVertex3i(side + scale*(x), side + scale*(y), col_height);
            glVertex3i(-side + scale*(x), side + scale*(y), col_height);

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
            glVertex3i(side + scale*(x), -side + scale*(y), col_height);
            glVertex3i(-side + scale*(x), -side + scale*(y), col_height);

            //Top
            glVertex3i(-side + scale*(x), side + scale*(y), -side);
            glVertex3i(side + scale*(x), side + scale*(y), -side);
            glVertex3i(side + scale*(x), side + scale*(y), col_height);
            glVertex3i(-side + scale*(x), side + scale*(y), col_height);

            //Left
            glVertex3i(-side + scale*(x), -side + scale*(y), -side);
            glVertex3i(-side + scale*(x), side + scale*(y), -side);
            glVertex3i(-side + scale*(x), side + scale*(y), col_height);
            glVertex3i(-side + scale*(x), -side + scale*(y), col_height);

            //Right
            glVertex3i(side + scale*(x), -side + scale*(y), -side);
            glVertex3i(side + scale*(x), side + scale*(y), -side);
            glVertex3i(side + scale*(x), side + scale*(y), col_height);
            glVertex3i(side + scale*(x), -side + scale*(y), col_height);

            glEnd();
        }
    }
}
void RenderMaze::DrawPixel(const Node element, const int colors[3], bool simple)
{
    
    if (use_3d == true)
    {
        double cx = element.x*scale; //0,0,0, 5, 36,18
        double cy = element.y*scale;
        double cz = 10 + (double)side/2;
        double rad = (double)side;
        int divH = 36;
        int divP = 18;

        glBegin(GL_QUADS);
        for (int i = -divP; i < divP; ++i)
        {
            double p0 = (double)i*PI*0.5 / (double)divP;
            double p1 = (double)(i + 1)*PI*0.5 / (double)divP;
            for (int j = 0; j < divH; ++j)
            {
                double h0 = (double)j*2.0*PI / (double)divH;
                double h1 = (double)(j + 1)*2.0*PI / (double)divH;

                double x0 = cx + rad * cos(p0)*cos(h0);
                double y0 = cy + rad * sin(p0);
                double z0 = cz + rad * cos(p0)*sin(h0);

                double x1 = cx + rad * cos(p0)*cos(h1);
                double y1 = cy + rad * sin(p0);
                double z1 = cz + rad * cos(p0)*sin(h1);

                double x2 = cx + rad * cos(p1)*cos(h1);
                double y2 = cy + rad * sin(p1);
                double z2 = cz + rad * cos(p1)*sin(h1);

                double x3 = cx + rad * cos(p1)*cos(h0);
                double y3 = cy + rad * sin(p1);
                double z3 = cz + rad * cos(p1)*sin(h0);

                if (simple == false)
                {
                    if (0 != (i + j) % 2)
                    {
                        glColor3f(colors[0], colors[1], colors[2]);
                    }
                    else
                    {
                        glColor3f(colors[2], colors[2], colors[2]);
                    }
                }
                else
                {
                    glColor3f(colors[0], colors[1], colors[2]);
                }
                if (simple == true)
                {
                    glVertex3d(x0, y0, 11);
                    glVertex3d(x1, y1, 11);
                    glVertex3d(x2, y2, 11);
                    glVertex3d(x3, y3, 11);
                }
                else
                {
                    glVertex3d(x0, y0, z0);
                    glVertex3d(x1, y1, z1);
                    glVertex3d(x2, y2, z2);
                    glVertex3d(x3, y3, z3);
                }
            }
        }
        glEnd();
    }
    else
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
}
void RenderMaze::DrawPlayer(void)
{
    int player_color[3] = { 255, 0 ,0 };
    int entry_color[3] = { 60, 60 ,60 };
    int exit_color[3] = { 25, 125 ,55 };

    DrawPixel(M.player, player_color, false);
    DrawPixel(M.entry_loc, entry_color, true);
    DrawPixel(M.exit_loc, exit_color, true);
}
void RenderMaze::panUp(void)
{
    if (camera.y < (double)height*scale / 2 +  side * scale)
    {
        camera.y += scale / 2;
    }
}
void RenderMaze::panDown(void)
{
    if (camera.y > height*scale / 2 - side * scale)
    {
        camera.y -= scale / 2;
    }
}
void RenderMaze::panLeft(void)
{
    if (camera.x > (double)width*scale / 2 - side * scale) // 
    {
        camera.x -= scale / 2;
    }
}
void RenderMaze::panRight(void)
{
    if (camera.x < (double)width*scale / 2 + side * scale) //
    {
        camera.x += scale / 2;
    }
}
void RenderMaze::zoomIn(void)
{
	if (camera.z > 500)
	{
		camera.z -= scale / 2;
	}
}
void RenderMaze::zoomOut(void)
{
	if (camera.z < 1050)
	{
		camera.z += scale / 2;
	}
}
void RenderMaze::MovePlayer(const char direction)
{
    if (M.player.x == M.exit_loc.x && M.player.y == M.exit_loc.y)
    {
        is_done = true;
        is_won = true;
        timer_stop();
    }
    else
    {
        switch (direction)
        {
        case FSKEY_UP:
            if (use_3d)
            {
                if (M.player.y > (double)height / 2)
                {
                    panUp();
                }
                M.moveDown();
            }
            else
            {
                M.moveUp();
            }
            
            break;
        case FSKEY_DOWN:
            if (use_3d)
            {
                if (M.player.y < (double)height / 2) // - 2 * side
                {
                    panDown();
                }
                M.moveUp();
            }
            else
            {
                M.moveDown();
            }
            
            break;
        case FSKEY_LEFT:
            if (use_3d)
            {
                if (M.player.x < (double)width / 2)
                {
                    panLeft();
                }
            }
            M.moveLeft();
            break;
        case FSKEY_RIGHT:
            if (use_3d)
            {
                //printf("\n(%d->%d)", M.player.x, (double)width / 2);
                if (M.player.x > (double)width/ 2)
                {
                    panRight();
                }
            }
            M.moveRight();
            break;
        case FSKEY_W:
            panUp();
            break;
        case FSKEY_S:
            panDown();
            break;
        case FSKEY_A:
            panLeft();
            break;
        case FSKEY_D:
            panRight();
            break;
        case FSKEY_Q:
			zoomIn();
            break;
		case FSKEY_E:
			zoomOut();
			break;
		case FSKEY_I:
			// Not yet implemented. For future release
			// game_window instructions(400, 600, FSKEY_Y, FSKEY_N);
			// instructions.initialize();
			break;
        }
    }
}
void RenderMaze::timer_start()
{
    start_time = std::chrono::system_clock::now();
}
void RenderMaze::timer_stop()
{
    stop_time = std::chrono::system_clock::now();
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
	DrawPlayer();

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
	glRasterPos2d(wid - 200, hei - 20);
	std::string bar_version = "The Maze v.0.0.1.";
	YsGlDrawFontBitmap10x14(bar_version.c_str());


	{
		glColor4ub(100, 100, 100, 255);
		glBegin(GL_QUADS);
		glVertex2i(0, hei);
		glVertex2i(0, hei - 20);
		glVertex2i(wid, hei - 20);
		glVertex2i(wid, hei);
		glEnd();

		glColor3ub(200, 200, 200);
		glRasterPos2d(5, hei - 3);
		YsGlDrawFontBitmap10x14("Movement: [UP, DOWN, LEFT, RIGHT], Pan: [W, S, A, D], Zoom In/Out: [Q, E]");
	}

	{
		glColor4ub(100, 100, 100, 255);
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(0, 20);
		glVertex2i(wid, 20);
		glVertex2i(wid, 0);
		glEnd();

		glColor3ub(200, 200, 200);
		glRasterPos2d(20, 17);
		YsGlDrawFontBitmap10x14(bar_version.c_str());

		glRasterPos2d((int)wid / 2 - 20, 17);
		std::string bar_level = "Level ";
		bar_level.append(to_string(level));
		YsGlDrawFontBitmap10x14(bar_level.c_str());

		glRasterPos2d(wid - 220, 17);
		std::string bar_timer = "Time left: ";
		auto end = std::chrono::system_clock::now();
		double passed = std::chrono::duration_cast <std::chrono::milliseconds> (end - start_time).count();
		double count_down = time - passed / 1000;
		std::string time_str = to_string(count_down);
		bar_timer.append(time_str);
		bar_timer.append(" s");
		YsGlDrawFontBitmapDirect(bar_timer.c_str(), YsFont10x14, 10, 14);

		if (count_down <= 0.1)
		{
			is_done = true;
		}
	}

    
}
double RenderMaze::get_timer(void) 
{
    double final_time = std::chrono::duration_cast <std::chrono::milliseconds> (stop_time - start_time).count() / 1000;
    return final_time;
}
const int RenderMaze::get_level(void)
{
	return level;
}
