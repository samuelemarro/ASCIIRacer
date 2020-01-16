#include "Levels/Level.hpp"

Level::Level() {
	this->prevLevel = nullptr;
	this->nextLevel = nullptr;
}

Level::Level(int ptn, int ptp, float s, int d) : Level(){
	this->pointsToNextLevel = ptn;
	this->pointsToPrevLevel = ptp;
	this->speed = s;
	this->difficulty = d;
}

bool Level::changeLevel(int player_points) {
	return (player_points >= this->pointsToNextLevel) || (player_points <= this->pointsToPrevLevel);
}

Level* Level::NextLevel() {
	Level* nl = new Level(pointsToNextLevel + 100, pointsToNextLevel - 5, speed + 1, difficulty + 1);
	this->nextLevel = nl;
	nl->prevLevel = this;
	return nl;
}