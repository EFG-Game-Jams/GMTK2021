#include <algorithm>
#include "game.hpp"
#include <thread>
#include "level.hpp"

int main(int argc, char ** argv)
{
	Level level = Level::Unknown;
	if (argc == 3 && std::string(argv[1]).compare("/level") == 0)
	{
		if (std::string(argv[2]).compare("test") == 0)
		{
			level = Level::Test;
		}
		else if (std::string(argv[2]).compare("level0") == 0)
		{
			level = Level::Level0;
		}
	}

	Game game;

	unsigned const targetFrameTime = 16; // 60 FPS
	game.Run(targetFrameTime, level);

	return 0;
}