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
#include "game.h"
#include "fssimplewindow.h"
#include "game_menu.h"
#include "ysglfontdata.h"




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
    int counter;
    int duration;
    time_t start, end;
    
    
    FsOpenWindow(0,0,800,600,1);
    printf("WELCOME");
    GameMenu menu;
    EndGameMenu endmenu;
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
			game new_game;
			bool finished = new_game.run();
            //break; 
        }
    }
    printf("ESCAPED FROM MENU?");
    FsCloseWindow;
    time(&start);
    
    
    
    FsChangeToProgramDir();
    
    
    // US: I suspended it so the screen will be same dimensions each time.
    //FsOpenWindow(16, 16, x_size*f_scale, y_size*f_scale, 1, "24780 Final Project: The Maze");
	
	

    //printf("Duration is %d seconds",duration);
    return 0;
}
