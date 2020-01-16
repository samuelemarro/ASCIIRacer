#pragma once

#include "GameObjects/LevelObjects/Border.hpp"

using std::pair;
using std::make_pair;

class Level {
public:
	int pointsToNextLevel;
	int pointsToPrevLevel;
	double speed;
	int difficulty;

	int roadWidth;
	int road_leftposition;

	Level* prevLevel;
	Level* nextLevel;

	Level();
	Level(int ptn, int ptp, float s, int d, int rw, int rlp);

	Level* NextLevel(int player_points);
	bool changeLevel(int player_points);
	pair<Border*, Border*> generateRoad();
};

typedef Level* ptr_Level;