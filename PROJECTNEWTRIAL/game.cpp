#include <stdio.h>
#include "game.h"
#include "fssimplewindow.h"
#include "rendermaze.h"

void RenderGame(void *incoming)
{
	RenderMaze *screen = (RenderMaze *)incoming;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bool use_3d = false;
	if (use_3d == false)
	{
		screen->DrawMap();
		//YsGlDrawFontBitmap16x24("24780 PROJECT: THE MAZE");
		screen->DrawPlayer();
	}
	else
	{
		screen->Render();
	}

	FsSwapBuffers();
}

game::game() : use_3d(true)
{
	int x_size = 7.9; //79
	int y_size = 5.9; //59
	int f_scale = 100; //10
	screen.initialize(x_size, y_size, f_scale);

}
bool game::run()
{
	FsRegisterOnPaintCallBack(RenderGame, &screen);

	bool terminate = false;
	while (terminate == false)
	{
		if (screen.is_done == true)
		{

			if (screen.is_won == true)
			{
				printf("Current map is ended and you won!");
			}
			else
			{
				printf("Current map is ended!");
			}
			terminate = true;
			//break;
		}
		FsPollDevice();
		auto key = FsInkey();
		switch (key)
		{
		case FSKEY_UP:
			//printf("%c", key);
			screen.MovePlayer(key);
			break;
		case FSKEY_DOWN:
			//printf("%c", key);
			screen.MovePlayer(key);
			break;
		case FSKEY_LEFT:
			//printf("%c", key);
			screen.MovePlayer(key);
			break;
		case FSKEY_RIGHT:
			//printf("%c", key);
			screen.MovePlayer(key);
		default:
			screen.MovePlayer(key);
			break;
		}
		FsPushOnPaintEvent();
		FsSleep(10);
	}
	if (screen.is_won == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}