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

auto name_input(void)
{
    TextInput txt;
    if (true == txt.Run("Enter Your Name>>"))
    {
        printf("You entered: %s\n", txt.GetString().GetPointer());
    }
    else
    {
        printf("Cancelled.\n");
    }

    return txt;//.GetString().GetPointer();
}

bool read_previous_data(int &level, int &timer, char playername[])
{
    char nameentry[256];
    auto input_txt = name_input();
    strcpy(nameentry, input_txt.GetString().GetPointer());

    if (nameentry[0] == 0)
    {
        printf("\nYou must enter a name, else the program cannot run!\n");
        return false;
    }

    FsChangeToProgramDir();

    int i = 0;
    char lastlevel[256];

    ifstream fin;
    fin.open("scoreboard.txt");
    if (fin.fail())
    {
        cout << "Database not found. Creating new one. Restart your game.\n";
        fopen("scoreboard.txt", "w+");
        return false;
    }
    
    string levels;
    //cout << "Please enter a name: ";
    //cin  >> search;
    string search = nameentry;
    strcpy(playername, nameentry);

    bool isFound = 0;
    while (!fin.eof())
    {
        string temp = "";
        string levelstring = "";
        string timerstring = "";
        getline(fin, temp);
        for (int i = 0; i < search.size(); i++)
        {
            if (temp[i] == search[i])
                isFound = 1;
            else
            {
                isFound = 0;
                break;
            }
        }
        if (isFound)
        {
            size_t pos = 0;
            if ((pos = temp.find(' ')) != std::string::npos)
            {
                //name
                temp.erase(0, pos + 1);
            }
            if ((pos = temp.find(' ')) != std::string::npos)
            {
                levelstring = temp;
                temp.erase(0, pos + 1);
                timerstring = temp;
            }
            else
            {
                levelstring = temp;
            }
            //printf("The size is %s\n",levelstring.c_str());
            level = atoi(levelstring.c_str());
            timer = atoi(timerstring.c_str());
            break;
        }
    }
    if (fin.eof() && (!isFound))
    {
        cout << "First time Player!\n";
        level = 0;
    }
    fin.close();
    printf("The last level is %d", level);
    return true;
}

void save_data(char *playername, int level, int timer)
{
    std::ofstream outfile;
    outfile.open("scoreboard.txt", std::ios_base::app);
    Player newentry;
    newentry.name = playername;
    newentry.level = level;
    newentry.timer = timer;
    std::string text = newentry.name;
    text += " " + std::to_string(newentry.level) + " " + std::to_string(newentry.timer) + "\n";
    outfile << text;

    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile("scoreboard.txt");
    while (std::getline(myfile, line))
        ++number_of_lines;
    std::cout << "Number of lines in text file: " << number_of_lines;
}

int main(void)
{
    int counter;
    int duration;
    int level = 0;
    int timer = 30;
    bool terminate = true;
    bool lets_play = false;
    bool lets_main = true;
    char playername[256];
    std::ofstream points;
    
    time_t start, end;
    
    FsChangeToProgramDir();
    
    FsOpenWindow(0,0,800,600,1,"The Maze: Final Project for 24-780 Fall 18");
    GameMenu menu;
    EndGameMenu endmenu;
    NextGameMenu nextmenu;
    PauseGameMenu pausemenu;
    //srand(time(nullptr));
    
	if (read_previous_data(level, timer, playername) == true)
	{
		terminate = false;
	}

	while (terminate == false)
	{
		//Main Menu
		if (lets_main == true)
		{
			for (;;)
			{
				menu.Run();
				if (FSKEY_ESC == menu.lastKey) //FSKEY_ESC == menu.lastKey //test.rejected == true
				{
					lets_play = false;
					lets_main = false;
					terminate = true;
					break;
				}
				else if (FSKEY_S == menu.lastKey) //FSKEY_S==menu.lastKey //test.accepted == true
				{
					//FSKEY_NULL!=FsInkey(); 
					printf("Welcome to the game!\n");
					lets_play = true;
					lets_main = false;
					break;
				}
			}
		}

		//Create Game
		if (lets_play == true)
		{
			for (;;)
			{
				game new_game(level, timer);
				bool finished = new_game.run();
				bool abort_game = new_game.is_abort;
				double timespentingame = new_game.get_timer();
				const double ttime = timespentingame;
				if (finished == true)
				{
					nextmenu.Run();
					if (FSKEY_ESC == nextmenu.lastKey || FSKEY_N == nextmenu.lastKey)
					{
						lets_play = false;
						lets_main = true;
						break; //Terminate the program
					}
					else if (FSKEY_S == nextmenu.lastKey || FSKEY_Y == nextmenu.lastKey)
					{
                        level += 1;
                        timer = (int)timespentingame + 1;
					}
					//game new_game(level,300);
					//bool finished = new_game.run();
				}
				else if (finished == false)
				{
					printf("%d", abort_game);
					if (abort_game == true)
					{
						abort_game = false;
						pausemenu.Run();
						if (FSKEY_ESC == pausemenu.lastKey || FSKEY_N == pausemenu.lastKey)
						{
							lets_play = false;
							lets_main = true;
							break; //Terminate the program
						}
						else if (FSKEY_S == pausemenu.lastKey || FSKEY_Y == pausemenu.lastKey)
						{
							lets_play = true;
							lets_main = false;
						}
					}
					else
					{
						timer += 2;
						endmenu.Run();
						if (FSKEY_ESC == endmenu.lastKey || FSKEY_N == endmenu.lastKey)
						{
							lets_play = false;
							lets_main = true;
							//terminate = true;
							break; 
						}
						else if (FSKEY_S == endmenu.lastKey || FSKEY_Y == endmenu.lastKey)
						{
						}
					}

				}
			}
		}

	}
	save_data(playername, level, timer);

	printf("\n Last level played: %d", level);
	printf("\n Saved\n");
    FsCloseWindow();
    //time(&start);
    

    return 0;
}
