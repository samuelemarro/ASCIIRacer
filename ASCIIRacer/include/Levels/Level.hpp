#pragma once

#include "GameObjects/GameObject.hpp"

#include <queue>

using std::queue;

class Level {
private:
	queue <ptr_GameObject> map;

public:
	int pointsToNextLevel;
	int pointsToPrevLevel;
	double speed;    // forse meglio che sia un int? da capire
	int difficulty;

	// forse inutili?
	int roadWidth;
	int road_leftposition;

	Level* prevLevel;
	Level* nextLevel;

	Level();
	Level(int ptn, int ptp, float s, int d, int rw, int rlp);

	Level* NextLevel(int player_points);
	bool changeLevel(int player_points);
};

typedef Level* ptr_Level;