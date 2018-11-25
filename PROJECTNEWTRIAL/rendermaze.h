//
//  rendermaze.h
//  PROJECTNEWTRIAL
//
//  Created by usoysal on 11/23/18.
//  Copyright © 2018 usoysal. All rights reserved.
//

#include "maze.h"

#ifndef RMAZE_FP_GAME_24780
#define RMAZE_FP_GAME_24780

class RenderMaze
{
private:
    maze M;
    int width, height, scale;
public:
	bool is_done;
	bool is_won;
    RenderMaze(void);
    RenderMaze(const int w, const int h, const int f);
    ~RenderMaze(void);
    void CleanUp(void);
    void initialize(void);
    void initialize(const int w, const int h, const int f);
    void MovePlayer(const char direction);
    void DrawMap(void);
	void DrawPixel(const Node element, const int colors[3]);
    void DrawPlayer(void);
};

#endif
