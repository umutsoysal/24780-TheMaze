//
//  shootinggame.h
//  PROJECTNEWTRIAL
//
//  Created by usoysal on 11/24/18.
//  Copyright © 2018 usoysal. All rights reserved.
//

#ifndef GAME_MENU_H_INCLUDED
#define GAME_MENU_H_INCLUDED

//TEST NEW MENU 
class GameObject
{
    public:
    int x,y;
};
class GameObjectWithState : public GameObject
{
    public:
    int state;
};
class GameMenu
{
    public:
    int lastKey;
    void Run(void);
};
class EndGameMenu
{
    public:
    int lastKey;
    int duration; 
    void Run(void);
    EndGameMenu();   // Constructor
    ~EndGameMenu();  // Destructor
    void CleanUp(void);
};

class NextGameMenu
{
public:
    int lastKey;
    int duration;
    void Run(void);
    NextGameMenu();   // Constructor
    ~NextGameMenu();  // Destructor
    void CleanUp(void);
};



/*
class ShootingGame;

class Player : public GameObject
{
    public:
    void Initialize(void);
    void Draw(void);
    void KeyIn(int key,ShootingGame &game);
};

class Target;

class Missile : public GameObjectWithState
{
    public:
    void Initialize(void);
    bool Launch(int x,int y);
    void Move(int mv);
    void Draw(void);
    void SpecialEffect(void);
    bool CheckCollision(Target &t);
};

class Target : public GameObjectWithState
{
    public:
    int v,w,h;
    void Initialize(void);
    void Move(void);
    void Draw(void);
    void Reverse(void);
};

class ShootingGame
{
    public:
    const int nMissile;
    const int nTarget;
    
    int nShot;
    Player player;
    Missile *missile;
    Target *target;
    
    ShootingGame();
    ShootingGame(int nMissile,int nTarget);
    ~ShootingGame();
    
    void Run(void);
    void Draw(void);
    
    static void Render(void *);
};

*/
#endif


