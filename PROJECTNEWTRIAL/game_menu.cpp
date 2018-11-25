//
//  shootinggame.cpp
//  PROJECTNEWTRIAL
//
//  Created by usoysal on 11/24/18.
//  Copyright © 2018 usoysal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "game_menu.h"
#include <string>
#include <iostream>


void RenderMenu(void *)
{
    std::string Something = "Some Text";
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,0,255);
    glRasterPos2d(32,48);
    YsGlDrawFontBitmap16x24("24780 PROJECT: THE MAZE");
    glRasterPos2d(32,72);
    YsGlDrawFontBitmap16x24("S.....START");
    glRasterPos2d(32,96);
    YsGlDrawFontBitmap16x24("ESC...QUIT");
    
    FsSwapBuffers();
}

void RenderEndMenu(void *)
{
    char myword[] = "Hello";
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,0,255);
    glRasterPos2d(32,48);
    YsGlDrawFontBitmap16x24(myword);
    glRasterPos2d(32,72);
    YsGlDrawFontBitmap16x24("S.....START");
    glRasterPos2d(32,96);
    YsGlDrawFontBitmap16x24("ESC...QUIT");
    FsSwapBuffers();
}
void RenderNextGameMenu(void *)
{
    char integer_string[32];
    int integer = endmenu.duration;
    sprintf(integer_string, "%d", integer);
    
    
    char myword[] = "YOU WON! ";
    
    char myword1[] = " seconds";
    
    strcat(myword, integer_string);
    strcat(myword, myword1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,0,255);
    glRasterPos2d(32,48);
    YsGlDrawFontBitmap16x24(myword);
    glRasterPos2d(32,72);
    YsGlDrawFontBitmap16x24("S.....START");
    glRasterPos2d(32,96);
    YsGlDrawFontBitmap16x24("ESC...QUIT");
    FsSwapBuffers();
}

void GameMenu::Run(void)
{
    FsRegisterOnPaintCallBack(RenderMenu,nullptr);
    printf("WHY BY PASS HERE?");
    for(;;)
    {
        FsPollDevice();
        lastKey=FsInkey();
        
        if(FSKEY_ESC==lastKey || FSKEY_S==lastKey)
        {
            break;
        }
        
        FsPushOnPaintEvent();
        FsSleep(10);
    }
}


void EndGameMenu::Run(void)
{
    FsRegisterOnPaintCallBack(RenderEndMenu,nullptr);
    for(;;)
    {
        FsPollDevice();
        lastKey=FsInkey();
        
        if(FSKEY_ESC==lastKey || FSKEY_S==lastKey)
        {
            break;
        }
        FsPushOnPaintEvent();
        FsSleep(10);
    }
}
EndGameMenu::EndGameMenu()
{
    duration=0;
}
EndGameMenu::~EndGameMenu()
{
    CleanUp();
}

void EndGameMenu::CleanUp(void)
{
    duration=0;
}


void NextGameMenu::Run(void)
{
    FsRegisterOnPaintCallBack(RenderNextGameMenu,nullptr);
    for(;;)
    {
        FsPollDevice();
        lastKey=FsInkey();
        
        if(FSKEY_ESC==lastKey || FSKEY_S==lastKey)
        {
            break;
        }
        FsPushOnPaintEvent();
        FsSleep(10);
    }
}
NextGameMenu::NextGameMenu()
{
    duration=0;
}
NextGameMenu::~NextGameMenu()
{
    CleanUp();
}

void NextGameMenu::CleanUp(void)
{
    duration=0;
}



////////////////////////////////////////////////////////////
/*
void Player::Initialize(void)
{
    x=400;
    y=550;
}

void Player::Draw(void)
{
    glColor3ub(0,255,0);
    
    glBegin(GL_QUADS);
    
    glVertex2i(x-15,y);
    glVertex2i(x+15,y);
    glVertex2i(x+15,y-10);
    glVertex2i(x-15,y-10);
    
    glVertex2i(x-5,y);
    glVertex2i(x-5,y-20);
    glVertex2i(x+5,y-20);
    glVertex2i(x+5,y);
    
    glEnd();
}
void Player::KeyIn(int key,ShootingGame &game)
{
    if(FSKEY_LEFT==key)
    {
        x-=20;
    }
    else if(FSKEY_RIGHT==key)
    {
        x+=20;
    }
    else if(FSKEY_SPACE==key)
    {
        for(int i=0; i<game.nMissile; ++i)
        {
            auto &m=game.missile[i];
            if(true==m.Launch(x,y))
            {
                ++game.nShot;
                break;
            }
        }
    }
}


void Missile::Initialize(void)
{
    printf("%s %d\n",__FUNCTION__,__LINE__);
    state=0;
}
bool Missile::Launch(int x,int y)
{
    if(0==state)
    {
        this->x=x;
        this->y=y;
        this->state=1;
        return true;
    }
    return false;
}
void Missile::Move(int mv)
{
    y-=mv;
    if(y<0)
    {
        state=0;
    }
}
void Missile::Draw(void)
{
    glColor3ub(255,0,0);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i(x,y+10);
    glEnd();
}

bool Missile::CheckCollision(Target &t)
{
    int dx=x-t.x;
    int dy=y-t.y;
    if(0<=dx && dx<=t.w && 0<=dy && dy<=t.h)
    {
        return true;
    }
    return false;
}

void Target::Initialize(void)
{
    printf("%s %d\n",__FUNCTION__,__LINE__);
    v=15+rand()%5;
    state=1;
    x=0;
    y=100+rand()%20;
    w=60+rand()%40;
    h=20;
}
void Target::Move(void)
{
    x+=v;
    if((800<x+w && 0<v) || (x<0 && v<0))
    {
        Reverse();
    }
}
void Target::Reverse(void)
{
    v=-v;
}
void Target::Draw(void)
{
    glColor3ub(0,255,255);
    glBegin(GL_QUADS);
    
    glVertex2i(x  ,y);
    glVertex2i(x+w,y);
    glVertex2i(x+w,y+h);
    glVertex2i(x  ,y+h);
    
    glEnd();
}



int mv=10;

ShootingGame::ShootingGame() : nMissile(3),nTarget(5)
{
    missile=new Missile[nMissile];
    target=new Target[nTarget];
}
ShootingGame::ShootingGame(int nm,int nt) : nMissile(nm),nTarget(nt)
{
    missile=new Missile[nMissile];
    target=new Target[nTarget];
}

ShootingGame::~ShootingGame()
{
    delete [] missile;
    delete [] target;
}

void ShootingGame::Render(void *contextPtr)
{
    ShootingGame *gamePtr;
    gamePtr=(ShootingGame *)contextPtr;
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    gamePtr->Draw();
    FsSwapBuffers();
}

void ShootingGame::Run(void)
{
    bool terminate=false;
    player.Initialize();
    
    nShot=0;
    
    FsRegisterOnPaintCallBack(Render,this);
    for(int j=0; j<nTarget; ++j)
    {
        auto &t=target[j];
        t.Initialize();
    }
    for(int i=0; i<nMissile; ++i)
    {
        auto &m=missile[i];
        m.Initialize();
    }
    
    while(true!=terminate)
    {
        FsPollDevice();
        auto key=FsInkey();
        
        if(FSKEY_ESC==key)
        {
            terminate=true;
        }
        else
        {
            player.KeyIn(key,*this);
        }
        
        for(int i=0; i<nMissile; ++i)
        {
            auto &m=missile[i];
            if(0!=m.state)
            {
                m.Move(mv);
            }
        }
        for(int j=0; j<nTarget; ++j)
        {
            auto &t=target[j];
            if(0!=t.state)
            {
                t.Move();
            }
        }
        
        for(int i=0; i<nMissile; ++i)
        {
            auto &m=missile[i];
            if(0!=m.state)
            {
                for(int j=0; j<nTarget; ++j)
                {
                    auto &t=target[j];
                    if(0!=t.state && true==m.CheckCollision(t))
                    {
                        printf("Hit!\n");
                        m.state=0;
                        t.state=0;
                        break;
                    }
                }
            }
        }
        
        
        {
            int nLiveTarget=0;
            for(int j=0; j<nTarget; ++j)
            {
                auto &t=target[j];
                if(0!=t.state)
                {
                    ++nLiveTarget;
                }
            }
            if(0==nLiveTarget)
            {
                printf("You've shot %d missiles.\n",nShot);
                break;
            }
        }
        
        
        FsPushOnPaintEvent();
        FsSleep(10);
    }
}

void ShootingGame::Draw(void)
{
    player.Draw();
    for(int i=0; i<nMissile; ++i)
    {
        auto &m=missile[i];
        if(0!=m.state)
        {
            m.Draw();
        }
    }
    for(int j=0; j<nTarget; ++j)
    {
        auto &t=target[j];
        if(0!=t.state)
        {
            t.Draw();
        }
    }
}
*/

