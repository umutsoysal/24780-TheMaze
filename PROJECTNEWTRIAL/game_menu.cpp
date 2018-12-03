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
#include <math.h>
#include "yspng.h"

//TEST NEW COMMENT LINE
void RenderMenu(void *)
{
    int x1=360;
    int y1=400;
    int h=160;
    int l=90;
    
    std::string Something = "Some Text";
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(100,0,0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 600);
    glVertex2i(800, 600);
    glVertex2i(800, 0);
    glEnd();
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,0,0);
    glRasterPos2d(260,168);
    YsGlDrawFontBitmap32x48("THE MAZE");
    glRasterPos2d(270,292);
    YsGlDrawFontBitmap20x32("S.....START");
    glRasterPos2d(270,336);
    YsGlDrawFontBitmap20x32("ESC...QUIT");
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
    glVertex2i(x1, y1);
    glVertex2i(x1, y1+h);
    glVertex2i(x1+l, y1+h);
    glVertex2i(x1+l, y1);
    glEnd();
    
    glColor3ub(255,255,255);
    glRasterPos2d(x1+l/2,y1+h/2);
    YsGlDrawFontBitmap20x32("?");
    
    glColor3ub(0,50,0);
    glBegin(GL_QUADS);
    glVertex2i(x1, y1);
    glVertex2i(x1+l/2, y1-(h/10));
    glVertex2i(x1+l/2, y1+h+h/10);
    glVertex2i(x1, y1+h);
    glEnd();
    
    
    /*
    YsRawPngDecoder png1, png2, png3, png4;
    png1.Decode("PSYCHEDELIC-1.png");
    png1.Flip();
    printf("W=%d H=%d\n", png1.wid, png1.hei);
    png2.Decode("PSYCHEDELIC-2.png");
    png2.Flip();
    printf("W=%d H=%d\n", png2.wid, png2.hei);
    png3.Decode("PSYCHEDELIC-3.png");
    png3.Flip();
    printf("W=%d H=%d\n", png3.wid, png3.hei);
    png4.Decode("PSYCHEDELIC-4.png");
    png4.Flip();
    printf("W=%d H=%d\n", png4.wid, png4.hei);
    glRasterPos2d(0, png1.hei);
    glDrawPixels(png1.wid, png1.hei, GL_RGBA, GL_UNSIGNED_BYTE, png1.rgba);
    */
    FsSwapBuffers();
}
void RenderEndMenu(void *)
{
    std::string Something = "Some Text";
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 600);
    glVertex2i(800, 600);
    glVertex2i(800, 0);
    glEnd();
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,0,0);
    glColor3ub(0,0,255);
    glColor3ub(0,0,0);
    glRasterPos2d(260,168);
    YsGlDrawFontBitmap32x48("TIME IS UP");
    glRasterPos2d(270,292);
    YsGlDrawFontBitmap20x32("RETRY");
    glRasterPos2d(270,336);
    YsGlDrawFontBitmap20x32("ESC...QUIT");
    
    FsSwapBuffers();
}
void RenderNextGameMenu(void *)
{

    std::string Something = "Some Text";
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 600);
    glVertex2i(800, 600);
    glVertex2i(800, 0);
    glEnd();
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,0,0);
    glRasterPos2d(260,168);
    YsGlDrawFontBitmap32x48("YOU WON");
    glRasterPos2d(270,286);
    YsGlDrawFontBitmap20x32("CONTINUE ?");
    glRasterPos2d(270,336);
    YsGlDrawFontBitmap20x32("ESC...QUIT");
    FsSwapBuffers();

}

void RenderPauseGameMenu(void *)
{
    std::string Something = "Some Text";
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(100,100,0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 600);
    glVertex2i(800, 600);
    glVertex2i(800, 0);
    glEnd();
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(0,0,0);
    glRasterPos2d(260,168);
    YsGlDrawFontBitmap32x48("PAUSE");
    glRasterPos2d(270,286);
    YsGlDrawFontBitmap20x32("CONTINUE");
    glRasterPos2d(270,336);
    YsGlDrawFontBitmap20x32("ESC...QUIT");
    FsSwapBuffers();
    
}






int GameMenu::Run(void)
{
    FsRegisterOnPaintCallBack(RenderMenu,nullptr);
    printf("WHY BY PASS HERE?");
    for(;;)
    {
        FsPollDevice();
        lastKey=FsInkey();
        
        if (FSKEY_S==lastKey)
        {
            return 1;
            break;
        }
        if(FSKEY_ESC==lastKey)
        {
            return 0;
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
        
        if(FSKEY_ESC==lastKey || FSKEY_S==lastKey || FSKEY_Y == lastKey || FSKEY_N == lastKey)
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


void PauseGameMenu::Run(void)
{
    FsRegisterOnPaintCallBack(RenderPauseGameMenu,nullptr);
    for(;;)
    {
        FsPollDevice();
        lastKey=FsInkey();
        
        if(FSKEY_ESC==lastKey || FSKEY_S==lastKey || FSKEY_Y == lastKey || FSKEY_N == lastKey)
        {
            break;
        }
        FsPushOnPaintEvent();
        FsSleep(10);
    }
}
PauseGameMenu::PauseGameMenu()
{
    duration=0;
}
PauseGameMenu::~PauseGameMenu()
{
    CleanUp();
}

void PauseGameMenu::CleanUp(void)
{
    duration=0;
}


