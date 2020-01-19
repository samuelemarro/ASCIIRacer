#include "Levels/Level.hpp"

Level::Level() {
	this->prevLevel = nullptr;
	this->nextLevel = nullptr;
}

Level::Level(int ptn, int ptp, double s, int d) : Level(){
	this->pointsToNextLevel = ptn;
	this->pointsToPrevLevel = ptp;
	this->speed = s;
	this->difficulty = d;
}

bool Level::changeLevel(int player_points) {
	return (player_points >= this->pointsToNextLevel) || (player_points <= this->pointsToPrevLevel);
}

Level* Level::NextLevel(int player_points) {
	if (player_points >= this->pointsToNextLevel) {
		Level* nl = new Level(pointsToNextLevel + 100*(difficulty + 1), pointsToNextLevel * 0.90, speed + (int)(difficulty % 3 == 0), difficulty + 1);
		this->nextLevel = nl;
		nl->prevLevel = this;
		return nl;
	}

	else if (player_points <= this->pointsToPrevLevel) {
		return this->prevLevel;
	}

	else return 0;		//Caso mai raggiunto poichè precondition: changeLevel == true
}