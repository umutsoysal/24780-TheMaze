#include "rendermaze.h"


class game
{
private:
	RenderMaze screen;
	int level;
	double difficulty;
	const bool use_3d;
public:
	game(void);
	bool run(void);
};