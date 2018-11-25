//
//  maze.cpp
//  PROJECTNEWTRIAL
//
//  Created by usoysal on 11/23/18.
//  Copyright © 2018 usoysal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


maze::maze() : wall('1'), path('0'), entry('X'), exit('O')
{
    nodes = nullptr;
    this->width = 0;
    this->height = 0;
}
void maze::CleanUp(void)
{
    if (nodes != nullptr)
    {
        delete[] nodes;
    }
    nodes = nullptr;
    width = 0;
    height = 0;
}
maze::~maze()
{
    CleanUp();
}
bool maze::initialize(int w, int h)
{
    CleanUp();
    
    width = w;
    height = h;
    nodes = (Node *)calloc(width * height, sizeof(Node));
    
    
    Node *n;
    
    if (nodes == nullptr) return true; //If we fail to allocate mem to nodes
    
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            n = nodes + i + j * width; //Specific node. Could use indexing instead
            if (i * j % 2)
            {
                n->x = i;
                n->y = j;
                n->dirs = 15; //Assume that all directions can be explored (4 youngest bits set)
                n->c = path;
            }
            else n->c = wall; //Add walls between nodes
        }
    }
    return false;
}
Node *maze::link(Node *n)
{
    //Connects node to random neighbor (if possible) and returns
    //address of next node that should be visited
    
    int x, y;
    char dir;
    Node *dest;
    
    //Nothing can be done if null pointer is given - return
    if (n == nullptr) return nullptr;
    
    //While there are directions still unexplored
    while (n->dirs)
    {
        //Randomly pick one direction
        dir = (1 << (rand() % 4));
        
        //If it has already been explored - try again
        if (~n->dirs & dir) continue;
        
        //Mark direction as explored
        n->dirs &= ~dir;
        
        //Depending on chosen direction
        switch (dir)
        {
            //Check if it's possible to go right
            case 1:
            if (n->x + 2 < width)
            {
                x = n->x + 2;
                y = n->y;
            }
            else continue;
            break;
            
            //Check if it's possible to go down
            case 2:
            if (n->y + 2 < height)
            {
                x = n->x;
                y = n->y + 2;
            }
            else continue;
            break;
            
            //Check if it's possible to go left
            case 4:
            if (n->x - 2 >= 0)
            {
                x = n->x - 2;
                y = n->y;
            }
            else continue;
            break;
            
            //Check if it's possible to go up
            case 8:
            if (n->y - 2 >= 0)
            {
                x = n->x;
                y = n->y - 2;
            }
            else continue;
            break;
        }
        
        //Get destination node into pointer (makes things a tiny bit faster)
        dest = nodes + x + y * width;
        
        //Make sure that destination node is not a wall
        if (dest->c == path)
        {
            //If destination is a linked node already - abort
            if (dest->parent != NULL) continue;
            
            //Otherwise, adopt node
            dest->parent = n;
            
            //Remove wall between nodes
            nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = path;
            
            //Return address of the child node
            return dest;
        }
    }
    
    //If nothing more can be done here - return parent's address
    return (Node *)n->parent;
}
void maze::generate(void)
{
	// Here we generate a map by running a binary tree
    Node *start, *last;
    if (nodes != nullptr)
    {
        //Setup start node
        start = nodes + 1 + width;
        start->parent = start;
        last = start;
        
        //Connect nodes until start node is reached and can't be left
        while ((last = link(last)) != start);
        //nodes[start->y*width + start->x].c = entry;
		entry_loc.c = entry;
		entry_loc.x = start->x;
		entry_loc.y = start->y;
		entry_loc.parent = start->parent;
        //nodes[(width-1)*(height-1)].c = exit;
		exit_loc.c = entry;
		exit_loc.x = nodes[5 * width + 1].x; //(width - 1)*(height - 1)
		exit_loc.y = nodes[5 * width + 1].y;
		exit_loc.parent = nodes[60].parent;
		printf("\nExit node: (%d, %d)\n", exit_loc.x, exit_loc.y);

        player.x = start->x;
        player.y = start->y;
		player.parent = start->parent;
        player.c = '*';
        
    }
    else
    {
        printf("Maze->Generate:You have to initialize the maze first!\n");
    }
    
}
char maze::getMapPixel(int x, int y)
{
    if (nodes != nullptr) //Adding this to prevent errors
    {
        if (x >= 0 && x <= width - 1)
        {
            if (y >= 0 && y <= height - 1)
            {
                return nodes[y*width + x].c;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
void maze::moveUp(void)
{
    int pos_x1 = player.x;
    int pos_y1 = player.y - 1;
    if (nodes[pos_y1*width + pos_x1].c == path)
    {
        --player.y;
    }
}
void maze::moveDown(void)
{
    int pos_x1 = player.x;
    int pos_y1 = player.y + 1;
    if (nodes[pos_y1*width + pos_x1].c == path)
    {
        ++player.y;
    }
}
void maze::moveLeft(void)
{
    int pos_x1 = player.x - 1;
    int pos_y1 = player.y;
    if (nodes[pos_y1*width + pos_x1].c == path)
    {
        --player.x;
    }
}
void maze::moveRight(void)
{
    int pos_x1 = player.x + 1;
    int pos_y1 = player.y;
    if (nodes[pos_y1*width + pos_x1].c == path)
    {
        ++player.x;
    }
}
void maze::PrintToTerminal()
{
    //For troubleshooting purposes, mostly
    for (int i = 0; i < height; i++)
    {
        
        for (int j = 0; j < width; j++)
        {
            
            printf("%c", nodes[j + i * width].c);
			printf("(%d,%d)", nodes[j + i * width].x, nodes[j + i * width].y);
        }
        printf("\n\n");
    }
}
