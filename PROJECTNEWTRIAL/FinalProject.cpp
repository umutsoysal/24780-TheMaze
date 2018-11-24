//
//  FinalProject.cpp
//  PROJECTNEWTRIAL
//
//  Created by usoysal on 11/23/18.
//  Copyright © 2018 usoysal. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "rendermaze.h"
#include "fssimplewindow.h"
#include "shootinggame.h"
#include "ysglfontdata.h"


void Render(void *incoming)
{
    RenderMaze *screen = (RenderMaze *)incoming;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    screen->DrawMap();
    YsGlDrawFontBitmap16x24("24780 PROJECT: THE MAZE");
    screen->DrawPlayer();
    FsSwapBuffers();
}








int main(void)
{
    // Load historical data file, if it exists
    // Generate main menu, which contains these options:
    //        1- Start Game [as Last User]
    //        1*- [Select a Different User / Or Create it]
    //        2- Exit
    // Upon selecting Start Game:
    //        Load User variables to determine difficulty level
    //        Generate a new maze/map
    //        Generate count down timer
    //        Monitor keyboard inputs for movement and queue movement sounds
    FsOpenWindow(0,0,800,600,1);
    printf("WELCOME");
    GameMenu menu;
    srand(time(nullptr));
    
    for(;;)
    {
        printf("TESST HERE?");  //
        menu.Run();
        if(FSKEY_ESC==menu.lastKey)
        {
            break;
        }
        else if(FSKEY_S==menu.lastKey)
        {
            break; // Should update here
        }
    }
    printf("ESCAPED FROM MENU?");
    FsCloseWindow;
    
    
    bool terminate = false;
    RenderMaze screen;
    int x_size = 79;
    int y_size = 59;
    int f_scale = 10;
    screen.initialize(x_size, y_size, f_scale);
    
    FsChangeToProgramDir();
    FsRegisterOnPaintCallBack(Render, &screen);
    
    // US: I suspended it so the screen will be same dimensions each time.
    //FsOpenWindow(16, 16, x_size*f_scale, y_size*f_scale, 1, "24780 Final Project: The Maze");
    while (terminate == false)
    {
        FsPollDevice();
        auto key = FsInkey();
        switch (key)
        {
            case FSKEY_ESC:
            menu.Run();
            if(FSKEY_ESC==menu.lastKey)
            {
                break;
            }
            else if(FSKEY_S==menu.lastKey)
            {
                break; // Should update here
            }
            //terminate = true;
            //break;
            case FSKEY_UP:
            printf("%c", key);
            screen.MovePlayer(key);
            break;
            case FSKEY_DOWN:
            printf("%c", key);
            screen.MovePlayer(key);
            break;
            case FSKEY_LEFT:
            printf("%c", key);
            screen.MovePlayer(key);
            break;
            case FSKEY_RIGHT:
            printf("%c", key);
            screen.MovePlayer(key);
            break;
        }
        FsPushOnPaintEvent();
        FsSleep(10);
    }
    return 0;
}
