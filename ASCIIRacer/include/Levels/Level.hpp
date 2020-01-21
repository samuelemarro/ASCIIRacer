#pragma once

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Road.hpp"

#include <queue>

using std::queue;
using std::vector;
using std::rand;

class Level {
private:
	int currentId;
	unsigned int seed;

public:
	int pointsToNextLevel;
	int pointsToPrevLevel;
	double speed;    // forse meglio che sia un int? da capire
	int difficulty;

	vector<int> removedIds;


	Level* prevLevel;
	Level* nextLevel;


	Level();
	Level(int ptn, int ptp, double s, int d);

	void prepareLevel();
	Level* newLevel(int player_points);
	bool changeLevel(int player_points);

	void generateLine(int roadPosition, int roadWidth);

};

typedef Level* ptr_Level;