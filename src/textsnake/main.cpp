#include <algorithm>
#include "game.hpp"
#include <thread>

int main(int argc, char ** argv)
{
	int level = -2;
	if (argc == 3 && std::string(argv[1]).compare("/level") == 0)
	{
		if (std::string(argv[2]).compare("test") == 0)
		{
			level = -1;
		}
		else
		{
			level = std::atoi(argv[2]);
		}
	}

	Game game;

	unsigned const targetFrameTime = 16; // 60 FPS
	game.Run(targetFrameTime, level);

	return 0;
}