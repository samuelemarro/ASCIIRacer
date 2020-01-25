#pragma once

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Road.hpp"
#include "Engine/System.hpp"

#include <numeric>

using std::vector;
using std::rand;
using std::accumulate;

class Level {
private:
	int currentId;
	unsigned int seed;
	float obstacleProbability[3] = { 0.0012, 0.0024, 0.0024 };
	float upgradeProbability[2] = { 0.0024, 0.0016 };

	float obstacleCumulative;
	float upgradeCumulative;
	float AIcarProbability;

public:
	int pointsToNextLevel;
	int pointsToPrevLevel;
	float speed;    // forse meglio che sia un int? da capire
	int difficulty;

	vector<int> removedIds;


	Level* prevLevel;
	Level* nextLevel;


	Level();
	Level(int ptn, int ptp, float s, int d);

	void prepareLevel();
	Level* newLevel(int player_points);
	bool changeLevel(int player_points);

	void generateLine(int roadPosition, int roadWidth);

};

typedef Level* ptr_Level;