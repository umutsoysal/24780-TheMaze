#include <stdio.h>
#include "game.h"
#include "fssimplewindow.h"
#include "rendermaze.h"

void RenderGame(void *incoming)
{
    RenderMaze *screen = (RenderMaze *)incoming;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bool use_3d = true;
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
game::game(void)
{
    game(50, 300);
}
game::game(int l = 10, double t = 300) //
{
    int wid, hei;
    FsGetWindowSize(wid, hei);
    this->level = 50 - l;
    int f_scale = 2*level; //10
    int x_size = (int) wid / f_scale - 1; //79 //16
    int y_size = (int) hei / f_scale - 1; //59 //12
    
    screen.initialize(x_size, y_size, f_scale, t, l);

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
        case FSKEY_ESC:
            terminate = true;
            break;
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
double game::get_timer()
{
    return 3.1415926535;
}
