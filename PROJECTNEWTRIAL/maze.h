

#ifndef MAZE_FP_GAME_24780
#define MAZE_FP_GAME_24780

class Node
{
    public:
    int x, y; // Node coordinates
    void *parent; //Pointer to parent node
    char c; //Map character
    char dirs; //Directions that still haven't been explored
    Node(void)
    {
        parent = nullptr;
    }
};

class maze
{
    private:
    Node *nodes; //The array of nodes that make up the maze
    int width; //Width of the maze (odd number)
    int height; //Height of the maze (odd number)
    char wall; //Character to return for walls
    char path; //Character to return for paths
    char entry; //Character to return for Entry Point
    char exit; //Character to return for Exit Point
    public:
    Node player; //The node for current player
	Node entry_loc; //The maze entry node.
	Node exit_loc;
    maze(void);
    void CleanUp(void);
    ~maze(void);
    bool initialize(int w, int h);
    Node *link(Node *n);
    void generate(void);
    char getMapPixel(int x, int y);
    void PrintToTerminal(void);
    void moveUp(void);
    void moveDown(void);
    void moveLeft(void);
    void moveRight(void);
};

#endif
