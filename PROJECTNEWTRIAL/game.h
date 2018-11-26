#include "rendermaze.h"


class game
{
private:
	RenderMaze screen;
	
public:
	int level;
	double difficulty;
	game(void);
	game(int l, int t);
	bool run(void);
	double get_timer(void);
};