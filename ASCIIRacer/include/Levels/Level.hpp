#pragma once

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Road.hpp"
#include "GameObjects/LevelObjects/Upgrade.hpp"
#include "GameObjects/LevelObjects/Obstacle.hpp"

#include <queue>

using std::queue;
using std::vector;
using std::rand;

class Level {
private:
	vector <ptr_GameObject> mapSlice;    //50x30 slice of map
	vector <vector<ptr_GameObject> > Map;    //vector of map slices
	int slicesCount;

public:
	int pointsToNextLevel;
	int pointsToPrevLevel;
	double speed;    // forse meglio che sia un int? da capire
	int difficulty;


	Level* prevLevel;
	Level* nextLevel;

	Level();
	Level(int ptn, int ptp, double s, int d);

	Level* NextLevel(int player_points);
	bool changeLevel(int player_points);

	void generateMap();
	void saveMap();
	void saveObject(ptr_GameObject gameObject);
	vector<ptr_GameObject> getMapLine(int roadIndex, ptr_GameObject Road_object, bool generateMap);

};

typedef Level* ptr_Level;