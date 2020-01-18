#include "Levels/Level.hpp"

Level::Level() {
	this->prevLevel = nullptr;
	this->nextLevel = nullptr;
}

Level::Level(int ptn, int ptp, float s, int d, int rw, int rlp) : Level(){
	this->pointsToNextLevel = ptn;
	this->pointsToPrevLevel = ptp;
	this->speed = s;
	this->difficulty = d;
	this->roadWidth = rw;
	this->road_leftposition = rlp;
}

bool Level::changeLevel(int player_points) {
	return (player_points >= this->pointsToNextLevel) || (player_points <= this->pointsToPrevLevel);
}

Level* Level::NextLevel(int player_points) {
	if (player_points >= this->pointsToNextLevel) {
		Level* nl = new Level(pointsToNextLevel + 100, pointsToNextLevel - 5, speed + 1, difficulty + 1, roadWidth, road_leftposition);
		this->nextLevel = nl;
		nl->prevLevel = this;
		return nl;
	}

	else if (player_points <= this->pointsToPrevLevel) {
		return this->prevLevel;
	}

	else return 0;		//Caso mai raggiunto poichè precondition: changeLevel == true
}