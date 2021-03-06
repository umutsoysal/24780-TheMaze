#include <stdio.h>
#include "game.h"
#include "fssimplewindow.h"
#include "rendermaze.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"

void RenderGame(void *incoming)
{
    RenderMaze *screen = (RenderMaze *)incoming;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

    bool use_3d = true;
    if (use_3d == false)
    {
        screen->DrawMap();
        screen->DrawPlayer();
    }
    else
    {
        screen->Render();
    }

    FsSwapBuffers();
}
game::game(void)
{
    game(50, 300);
}
game::game(int l, double t) //
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	if (l < 50)
	{
		this->level = 50 - l;
	}
	else
	{
		this->level = 49;
		printf("\nYou have reached the highest level possible.");
	}
	int f_scale = 2*level; //10
    int x_size = (int) wid / f_scale; //79 //16
    int y_size = (int) hei / f_scale; //59 //12

	x_size = x_size + (x_size + 1) % 2;
	y_size = y_size + (y_size + 1) % 2;
    
    screen.initialize(x_size, y_size, f_scale, t, l);
    
    is_abort=false;
}
bool game::run()
{
    FsRegisterOnPaintCallBack(RenderGame, &screen);

	YsSoundPlayer player;
	player.MakeCurrent();
	player.Start();
	YsSoundPlayer::SoundData wav;
	//Of course our background music was created by someone else
	//And we are using it under	an Attribution License
	//The author calls himself TheDweebMan, and the file can 
	//be downloaded from:
	//https://freesound.org/people/TheDweebMan/sounds/277192/
	if (YSOK != wav.LoadWav("background.wav")) 
	{
		printf("Error -> Cannot load!\n");
	//	return 1;
	}
	player.PlayBackground(wav);

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
            //is_abort = true;
            //break;
        }
        FsPollDevice();
        auto key = FsInkey();
        switch (key)
        {
        case FSKEY_ESC:
            terminate = true;
            is_abort = true;
            break;
        default:
            screen.MovePlayer(key);
            break;
        }
        FsPushOnPaintEvent();
        FsSleep(10);
    }
	
	player.End();

    if (screen.is_won == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
double game::get_timer()
{
    return screen.get_timer();
}
