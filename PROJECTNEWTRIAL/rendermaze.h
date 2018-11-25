

#include "maze.h"
#include "framework3d.h"

#ifndef RMAZE_FP_GAME_24780
#define RMAZE_FP_GAME_24780

const double PI = 3.14159265;

class RenderMaze
{
private:
    maze M;
    int width, height, scale;
	int side; //Refers to width of each 3d object. 
	bool use_3d;
public:
	bool is_done;
	bool is_won;
	CameraObject camera;
    RenderMaze(void);
    RenderMaze(const int w, const int h, const int f);
    ~RenderMaze(void);
    void CleanUp(void);
    void initialize(void);
    void initialize(const int w, const int h, const int f);
    void MovePlayer(const char direction);
    void DrawMap(void);
	void Draw3DMap(void);
	void DrawPixel(const Node element, const int colors[3], bool simple = true);
    void DrawPlayer(void);
	void Render(void);
};

#endif
