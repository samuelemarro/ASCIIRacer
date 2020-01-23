#include "Levels/Level.hpp"
#include "Engine/System.hpp"
#include "Engine/GameEngine.hpp"
#include "Scenes/GameScene.hpp"
#include "GameObjects/LevelObjects/Obstacle.hpp"
#include "GameObjects/LevelObjects/Upgrade.hpp"
#include "GameObjects/LevelObjects/AICar.hpp"

Level::Level() {
	this->prevLevel = nullptr;
	this->nextLevel = nullptr;
	this->currentId = 0;
	this->seed = -1;
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

void Level::prepareLevel()
{
	if (this->seed == -1) {
		this->seed = time(NULL);
	}
	srand(this->seed);
	this->currentId = 0;
}

Level* Level::newLevel(int player_points) {
	if (player_points >= this->pointsToNextLevel) {
		if (this->nextLevel == NULL) {
			Level* nl = new Level(pointsToNextLevel + 100 * (difficulty + 1), pointsToNextLevel * 0.90, speed + 1, difficulty + 1);
			this->nextLevel = nl;
			nl->prevLevel = this;
			nl->nextLevel = NULL;
			return nl;
		}
		else
			return this->nextLevel;
	}

	else if (player_points <= this->pointsToPrevLevel) {
		return this->prevLevel;
	}

	else return 0;		//Caso mai raggiunto poichè precondition: changeLevel == true
}

void Level::generateLine(int roadPosition, int roadWidth) {
	float obstacleProbability = 0.0015;
	float upgradeProbability = 0.0015;
	float AIcarProbability = 0.0005;

	GameScene* scene = (GameScene*)GameEngine::currentScene;
	
	for (int i = 1; i < roadWidth - 1; i++) {
		float r = System::randomFloat();

		if (r < obstacleProbability) {
			//Genera ostacolo
			if (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) {
				Obstacle* obstacle = new Obstacle(Point2D(roadPosition + i, 0), this->difficulty * 15, this, currentId);    //dato da speed * 2(sec che voglio che mi riduca per dover arrivare al next)
				obstacle->velocity.y = this->speed;
				obstacle->velocity.x = 0;

				//test
				//obstacle->sprite[0][0].character = '0' + currentId;
				//test

				scene->addGameObject(obstacle);
			}
			currentId++;
		}
		else if (r < obstacleProbability + upgradeProbability) {
			//Genera upgrade
			if (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) {
				Upgrade* upgrade = new Upgrade(Point2D(roadPosition + i, 0), this->difficulty * 100, this, currentId);
				upgrade->velocity.y = this->speed;
				upgrade->velocity.x = 0;

				//test
				//upgrade->sprite[0][0].character = '0' + currentId;
				//test

				scene->addGameObject(upgrade);
			}
			currentId++;
		}
		else if (r < obstacleProbability + upgradeProbability + AIcarProbability) {
			//Genera AIcar
			if (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) {
				AICar* aicar = new AICar(Point2D(roadPosition + i, -2), this->difficulty * 50);
				aicar->velocity.y = this->speed * 0.5;
				aicar->velocity.x = 0;

				//test
				aicar->sprite[1][1].character = '0' + currentId;
				//test
				
				scene->addGameObject(aicar);
			}
			currentId++;
		}
	}
}
