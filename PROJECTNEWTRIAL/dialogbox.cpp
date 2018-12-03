//
//  dialogbox.cpp
//  GAMEMENUPROJECT
//
//  Created by usoysal on 12/1/18.
//  Copyright © 2018 usoysal. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "dialogbox.h"

using namespace std;

char *MyFgets(char str[],int maxn,FILE *fp)
{
    auto r=fgets(str,maxn,fp);
    if(nullptr!=r)
    {
        for(int i=strlen(str)-1; 0<=i; --i)
        {
            if(str[i]<' ')
            {
                str[i]=0;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        str[0]=0;
    }
    return r;
}

int ParseString(int wordTop[],int wordLen[],int maxlen,char input[])
{
    if(0==maxlen)
    {
        return 0;
    }
    
    int state=0;
    int wordCount=0;
    for(int i=0; 0!=input[i]; ++i)
    {
        if(0==state)
        {
            if(' '<input[i])
            {
                wordTop[wordCount]=i;
                wordLen[wordCount]=1;
                state=1;
                ++wordCount;
            }
        }
        else if(1==state)
        {
            if(input[i]<=' ')
            {
                state=0;
                if(maxlen<=wordCount)
                {
                    break;
                }
            }
            else
            {
                ++wordLen[wordCount-1];
            }
        }
    }
    
    return wordCount;
}

void ExtractWord(char word[],int maxlen,char input[],int top,int len)
{
    int nChar;
    if(maxlen-1>len)
    {
        nChar=len;
    }
    else
    {
        nChar=maxlen-1;
    }
    
    for(int i=0; i<nChar; ++i)
    {
        word[i]=input[top+i];
    }
    word[nChar]=0;
}




template <class T>
GenericArray<T>::GenericArray()
{
    len=0;
    dat=nullptr;
}
template <class T>
GenericArray<T>::~GenericArray()
{
    CleanUp();
}
template <class T>
void GenericArray<T>::CleanUp(void)
{
    if(nullptr!=dat)
    {
        delete [] dat;
    }
    dat=nullptr;
    len=0;
}
template <class T>
void GenericArray<T>::Resize(int newLen)
{
    auto newDat=new T [newLen];
    
    for(int i=0; i<len && i<newLen; ++i)
    {
        newDat[i]=dat[i];
    }
    
    CleanUp();
    dat=newDat;
    len=newLen;
}
template <class T>
int GenericArray<T>::GetLength(void) const
{
    return len;
}

template <class T>
T *GenericArray<T>::GetPointer(void)
{
    return dat;
}
template <class T>
const T *GenericArray<T>::GetPointer(void) const
{
    return dat;
}





TextString::TextString()
{
}

TextString::TextString(const TextString &incoming)
{
    Set(incoming.GetPointer());
}
TextString::TextString(const char from[])
{
    Set(from);
}

TextString::~TextString()
{
    CleanUp();
}

void TextString::Set(const char from[])
{
    auto str=GenericArray::GetPointer();
    if(from!=str)
    {
        CleanUp();
        if(nullptr!=from)
        {
            int l=strlen(from);
            Resize(l+1);
            str=GenericArray::GetPointer();
            strcpy(str,from);
        }
    }
}

void TextString::Add(const char from[])
{
    for(int i=0; 0!=from[i]; ++i)
    {
        Add(from[i]);
    }
}

void TextString::Add(const char c)
{
    // If l=1:
    // str[0]  str[1]
    //  'a'      0
    // newStr[0]   newStr[1]   newStr[2]
    //   'a'           c          0
    
    int l=Strlen();
    
    Resize(l+1+1);
    
    auto str=GenericArray::GetPointer();
    str[l  ]=c;
    str[l+1]=0;
}

void TextString::BackSpace(void)
{
    if(0<Strlen())
    {
        int l=Strlen();
        Resize(l);
        auto str=GenericArray::GetPointer();
        str[l-1]=0;
    }
}

const char *TextString::Fgets(FILE *fp)
{
    CleanUp();
    
    char s[16];
    bool eof=true;
    while(nullptr!=fgets(s,15,fp))
    {
        eof=false;
        for(int i=0; s[i]!=0; ++i)
        {
            if('\n'==s[i])
            {
                return GetPointer();
            }
            else
            {
                Add(s[i]);
            }
        }
    }
    
    if(eof==true)
    {
        return nullptr;
    }
    return GetPointer();
}

//void TextString::DeleteLastControlCode(void);

const char *TextString::GetPointer(void) const
{
    auto str=GenericArray::GetPointer();
    if(nullptr==str)
    {
        return "";
    }
    else
    {
        return str;
    }
}

const int TextString::Strlen(void) const
{
    auto str=GenericArray::GetPointer();
    if(nullptr==str)
    {
        return 0;
    }
    else
    {
        return strlen(str);
    }
}

void TextString::Print(void) const
{
    printf("%s\n",GetPointer());
}

TextString &  TextString::operator=(const TextString &   from)
{
    this->Set(from.GetPointer());
    return *this;
}



TextInput::TextInput()
{
}
TextInput::~TextInput()
{
    CleanUp();
}
void TextInput::CleanUp(void)
{
    title.CleanUp();
    str.CleanUp();
}

void RenderTextInput(void *incoming)
{
    TextInput *txtPtr=(TextInput *)incoming;
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    txtPtr->Draw();
    FsSwapBuffers();
}

bool TextInput::Run(const char title[])
{
    FsRegisterOnPaintCallBack(RenderTextInput,this);
    
    CleanUp();
    this->title.Set(title);
    for(;;)
    {
        FsPollDevice();
        auto key=FsInkey();
        if(FSKEY_ESC==key)
        {
            str.CleanUp();
            return false;
        }
        if(FSKEY_ENTER==key)
        {
            return true;
        }
        if(FSKEY_BS==key)
        {
            str.BackSpace();
        }
        
        auto c=FsInkeyChar();
        if(' '<=c && c<128)
        {
            str.Add(c);
        }
        
        FsPushOnPaintEvent();
        FsSleep(10);
    }
    
    FsRegisterOnPaintCallBack(nullptr,nullptr);
}

const TextString &TextInput::GetString(void) const
{
    return str;
}
void TextInput::Draw(void) const
{
    glColor3ub(0,0,255);
    
    glRasterPos2d(32,32);
    YsGlDrawFontBitmap12x16(title.GetPointer());
    
    auto cpy=str;
    switch(time(nullptr)%2)
    {
        case 0:
            cpy.Add("|");
            break;
        default:
            cpy.Add("_");
            break;
    }
    
    glRasterPos2d(32,48);
    YsGlDrawFontBitmap12x16(cpy.GetPointer());
}


Parser::Parser()
{
    nw=0;
    str=nullptr;
    wTop=nullptr;
    wLen=nullptr;
}
Parser::~Parser()
{
    CleanUp();
}
void Parser::CleanUp(void)
{
    nw=0;
    if(nullptr!=str)
    {
        delete [] str;
        str=nullptr;
    }
    if(nullptr!=wTop)
    {
        delete [] wTop;
        wTop=nullptr;
    }
    if(nullptr!=wLen)
    {
        delete [] wLen;
        wLen=nullptr;
    }
}
int Parser::Parse(char incoming[])
{
    int maxlen=(strlen(str)+1)/2;
    CleanUp();
    
    str=new char [strlen(incoming)+1];
    strcpy(str,incoming);
    wTop=new int [maxlen];
    wLen=new int [maxlen];
    return ParseString(wTop,wLen,maxlen,str);
}



Scoreboard::Scoreboard()
{
    nVtx=0; // number of entries in the database
    vtx=nullptr;
    temp=nullptr;
}
Scoreboard::~Scoreboard()
{
    CleanUp();
}
void Scoreboard::CleanUp(void)
{
    nVtx=0;
    if(nullptr!=vtx)
    {
        delete [] vtx;
        vtx=nullptr;
        delete [] temp;
        temp=nullptr;
    }
}
void Scoreboard::ReadFile(char fName[])
{
    FILE *fp=fopen(fName,"r");
    if(nullptr!=fp)
    {
        CleanUp();
        char str[256];
        if(nullptr!=fgets(str,255,fp))
        {
            nVtx=atoi(str);
            printf("%d Player Record\n",nVtx);
            int n=0;
            vtx=new Player [nVtx];
            temp=new Player [1];
            for(int i=0; i<nVtx; ++i)
            {
                if(nullptr!=fgets(str,255,fp))
                {
                    int nw,wTop[2],wLen[2];
                    if(2<=ParseString(wTop,wLen,2,str))
                    {
                        vtx[n].name=str;//+wTop[0];
                        vtx[n].level=atoi(str+wTop[1]);
                        printf("%s",vtx[n].name);
                        printf("%d\n",vtx[n].level);
                        ++n;
                        
                    }
                }
            }
            //printf("%d registred player number.\n",n);
            fclose(fp);
        }
    }
}
void Scoreboard::Sort() //Bubble S
{
    int swapcounter=0;
    for(int i=0; i<nVtx; ++i)
    {
        for(int j=i+1; j<nVtx; ++j)
        {
            if(vtx[i].level>vtx[j].level)
            {
                temp[1]=vtx[i];
                vtx[i]=vtx[j];
                vtx[j]=temp[1];
                swapcounter=swapcounter+1;
            }
        }
    }
    printf("TOP PLAYERS\n");
    printf("1. %d\n", vtx[nVtx-1].level);
    printf("2. %d\n", vtx[nVtx-2].level);
    printf("3. %d\n", vtx[nVtx-3].level);
}
