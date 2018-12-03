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
#include "dialogbox.h"
#include <iostream>
#include <fstream>

using namespace std;

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
    char playername[256];
    std::ofstream points;
    
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
            FSKEY_NULL!=FsInkey();  // An attemp to clear last key input for data search
            printf("Welcome to the game!\n");
            // OPEN A DIALOG BOX AND ASK TO PROMPT A USER NAME ONE WORD ONLY, NO SPACE
            //FsOpenWindow(0,0,800,600,1);
            char nameentry[256];
            TextInput txt;
            if(true==txt.Run("Enter Your Name>>"))
            {
                printf("You entered: %s\n",txt.GetString().GetPointer());
            }
            else
            {
                printf("Cancelled.\n");
            }
            //FsCloseWindow(); // It does not work but we will open a new window anyway
            // CLOSE THE DIALOGBOX
            strcpy(nameentry, txt.GetString().GetPointer() ); // Convert dialogbox output to a char array
            printf("TEST You entered: %s\n",nameentry);
            // CHECK IF THE ENTERED NAME IS IN THE GAME HISTORY
            int i=0;
            char lastlevel[256];
            
            ifstream fin;
            fin.open("scoreboard.txt");
            if(fin.fail())
            {
                cout << "Database error: Input file opening failed.\n";
                exit(1);
            }
            string levels;
            //cout << "Please enter a name: ";
            //cin  >> search;
            string search= nameentry;
            strcpy(playername,nameentry);
            
            bool isFound=0;
            while(!fin.eof())
            {
                string temp = "";
                string levelstring = "";
                getline(fin,temp);
                for(int i=0;i<search.size();i++)
                {
                    if(temp[i]==search[i])
                        isFound = 1;
                    else
                    {
                        isFound =0;
                        break;
                    }
                }
                if(isFound)
                {
                    //cout << "Level is: ";
                    for(int i = search.size()+1;i<temp.size();i++)
                    {
                        cout << temp[i];
                        levelstring+=temp[i];
                    }
                    //printf("The size is %s\n",levelstring.c_str());
                    //level = atoi(&temp[i]);
                    level=atoi(levelstring.c_str());
                    break;
                }
            }
            if(fin.eof()&&(!isFound))
            {
                cout << "First time Player!\n";
                level=0;
            }
            fin.close();
            printf("The last level is %d",level);
            
            
            
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
      
        printf("\n Last level is  %d",level);
        printf("\n Saved\n");
        
        std::ofstream outfile;
        outfile.open("scoreboard.txt", std::ios_base::app);
        Player newentry;
        newentry.name=playername;
        newentry.level=level;
        std::string text = newentry.name;
        text += " "+std::to_string(newentry.level)+"\n";
        outfile << text;
        
        int number_of_lines = 0;
        std::string line;
        std::ifstream myfile("scoreboard.txt");
        while (std::getline(myfile, line))
            ++number_of_lines;
        std::cout << "Number of lines in text file: " << number_of_lines;
        
    }
    FsCloseWindow;
    //time(&start);
    FsChangeToProgramDir();
    
    
    
    
    
    // US: I suspended it so the screen will be same dimensions each time.
    //FsOpenWindow(16, 16, x_size*f_scale, y_size*f_scale, 1, "24780 Final Project: The Maze");
    //printf("Just another test");
    //points.open ("gamedata.txt");
    //points << "an example of saved data";
    //points.close();
    //printf("Duration is %d seconds",duration);
    return 0;
}
