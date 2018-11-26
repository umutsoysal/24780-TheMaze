#include "rendermaze.h"


class game
{
private:
	RenderMaze screen;
	
public:
    bool is_abort;
	int level;
	double difficulty;
	game(void);
	game(int l, double t);
	bool run(void);
	double get_timer(void);
};
