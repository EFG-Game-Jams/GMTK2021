#pragma once
#include "noaisnake.hpp"
#include "randomsnake.hpp"
#include "playersnake.hpp"
#include "huntersnake.hpp"
#include "menusnake.hpp"
#include "clustersnake.hpp"
#include "color.hpp"
#include <memory>

namespace SnakeFactory
{
	std::unique_ptr<ClusterSnake> CreateCluster(COORD const position, MovingDirection const orientation, std::string const& letters, Color::Color const clearColor = Color::Color());
	std::unique_ptr<HunterSnake> CreateHunter(COORD const position, MovingDirection const orientation, std::string const & letters, Color::Color const clearColor = Color::Color());
	std::unique_ptr<PlayerSnake> CreatePlayer(COORD const position, MovingDirection const orientation, std::string const & letters, Color::Color const clearColor = Color::Color());
	std::unique_ptr<NoAiSnake> CreateNoAi(COORD const position, MovingDirection const orientation, std::string const & letters, Color::Color const clearColor = Color::Color());
	std::unique_ptr<RandomSnake> CreateRandom(COORD const position, MovingDirection const orientation, std::string const& letters, Color::Color const clearColor = Color::Color());
	std::unique_ptr<MenuSnake> CreateMenu(COORD const position, std::string const & letters, SnakeType const type);
};

