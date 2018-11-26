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
    int level = 0;
	int timer = 30;
    bool finished;
    time_t start, end;
    
    
    FsOpenWindow(0,0,800,600,1);
    printf("WELCOME");
    GameMenu menu;
    EndGameMenu endmenu;
    NextGameMenu nextmenu;
    PauseGameMenu pausemenu;
    srand(time(nullptr));
    
    for(;;) //EXPERIMENTAL
    {
        menu.Run();
        if(FSKEY_ESC==menu.lastKey)
        {
            break; //Terminate the program
        }
        else if(FSKEY_S==menu.lastKey)
        {
            for (;;)
            {
                game new_game(level,timer);
                bool finished = new_game.run();
                bool abort_game=new_game.is_abort;
                double timespentingame = new_game.get_timer();
                const double ttime=timespentingame;
                if (finished == true)
                {
                    nextmenu.Run();
                    if(FSKEY_ESC==nextmenu.lastKey)
                    {
                        break; //Terminate the program
                    }
                    else if(FSKEY_S==menu.lastKey)
                    {
						level += 1;
						timer = (int)timespentingame + 1;
                    }
                    //game new_game(level,300);
                    //bool finished = new_game.run();
                }
                else if (finished == false)
                {
                    printf("%d",abort_game);
                    if (abort_game == true)
                    {
                        abort_game=false;
                        pausemenu.Run();
                        if(FSKEY_ESC==pausemenu.lastKey)
                        {
                            break; //Terminate the program
                        }
                        else if(FSKEY_S==pausemenu.lastKey)
                        {
                        }
                    }else
                    {
                        timer += 2;
                        endmenu.Run();
                        if(FSKEY_ESC==endmenu.lastKey)
                        {
                            break; //Terminate the program
                        }
                        else if(FSKEY_S==endmenu.lastKey)
                        {
                        }
                    }
                
                }
            }
        }
        
    }
    FsCloseWindow;
    time(&start);
    FsChangeToProgramDir();
    
    // US: I suspended it so the screen will be same dimensions each time.
    //FsOpenWindow(16, 16, x_size*f_scale, y_size*f_scale, 1, "24780 Final Project: The Maze");
     printf("Just another test");
    

    //printf("Duration is %d seconds",duration);
    return 0;
}
