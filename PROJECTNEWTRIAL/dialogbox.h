//
//  dialogbox.h
//  GAMEMENUPROJECT
//
//  Created by usoysal on 12/1/18.
//  Copyright © 2018 usoysal. All rights reserved.
//

#ifndef dialogbox_h
#define dialogbox_h


#endif /* dialogbox_h */



template <class T>
class GenericArray
{
private:
    int len;
    T *dat;
public:
    GenericArray();
    ~GenericArray();
    void CleanUp(void);
    
    void Resize(int newLen);
    
    int GetLength(void) const;
    T *GetPointer(void);
    const T *GetPointer(void) const;
};


class TextString : public GenericArray <char>
{
public:
    TextString();
    TextString(const char from[]);
    TextString(const TextString &str);
    ~TextString();
    
    void Set(const char from[]);
    void Add(const char from[]);
    void Add(const char c);
    void BackSpace(void);
    const char *Fgets(FILE *fp);
    void DeleteLastControlCode(void);
    const char *GetPointer(void) const;
    const int Strlen(void) const;
    void Print(void) const;
    TextString &operator=(const TextString &from);
};



class TextInput
{
protected:
    TextString title;
    TextString str;
    
public:
    TextInput();
    ~TextInput();
    void CleanUp(void);
    
    bool Run(const char title[]);
    void Draw(void) const;
    const TextString &GetString(void) const;
};


class Parser
{
protected:
    int nw;
    int *wTop,*wLen;
    char *str;
    
public:
    Parser();
    ~Parser();
    void CleanUp(void);
    
    int Parse(char str[]);
    void GetWord(char wd[],int maxlen,int idx);
};

class Player
{
public:
    char *name;
    int level;
};
class Scoreboard
{
protected:
    int nVtx;
    Player *vtx;
    Player *temp;
public:
    Scoreboard();
    ~Scoreboard();
    void CleanUp(void);
    
    void ReadFile(char fName[]);
    void Sort(void);
    void Draw(void);
};
