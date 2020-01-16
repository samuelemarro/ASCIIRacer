#pragma once

class Level {
public:
	int pointsToNextLevel;
	int pointsToPrevLevel;

	double speed;

	int difficulty;

	Level* prevLevel;
	Level* nextLevel;

	Level();
	Level(int ptn, int ptp, float s, int d);

	Level* NextLevel();
	bool changeLevel(int player_points);
};

typedef Level* ptr_Level;