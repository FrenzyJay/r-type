#include "GameEngine.hpp"

// LE main
int main()
{
	srand(time(NULL));
	GameEngine	engine(900, 600);

	engine.start();
    return 0;
}

