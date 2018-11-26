#include "rendermaze.h"


class game
{
private:
	RenderMaze screen;
	
public:
	int level;
	double difficulty;
	game(void);
	game(int level, int time);
	bool run(void);
	double get_timer(void);
};