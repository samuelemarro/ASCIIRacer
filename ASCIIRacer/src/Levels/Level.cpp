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

Level::Level(int ptn, int ptp, float s, int d) : Level(){
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
	float obstacleProbability[] = { 0.0009, 0.0007, 0.0004 };
	//TODO: increase object probability as level increase (increase obstacle probability more than upgrade probability)
	float obstacleCumulative = accumulate(obstacleProbability, obstacleProbability + (sizeof(obstacleProbability) / sizeof(obstacleProbability[0])), 0.0);

	float upgradeProbability[] = { 0.0013, 0.0007 };
	//IDEM DI SOPRA
	float upgradeCumulative = accumulate(upgradeProbability, upgradeProbability + (sizeof(upgradeProbability) / sizeof(upgradeProbability[0])), 0.0);

	float AIcarProbability = 0.0005;

	GameScene* scene = (GameScene*)GameEngine::currentScene;
	
	for (int i = 1; i < roadWidth - 1; i++) {
		float r = System::randomFloat();

		if (r < obstacleCumulative) {
			//Genera ostacolo
			if (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) {
				bool placed = false;
				for (int j = 1; j <= (sizeof(obstacleProbability) / sizeof(obstacleProbability[0])) && !placed; j++) {
					if (r < accumulate(obstacleProbability, obstacleProbability + j, 0.0)) {
						//TODO: define obstacle damage depeding on type (aka j)
						Obstacle* obstacle = new Obstacle(Point2D(roadPosition + i, 0), this->difficulty * 15, j, this, currentId);    //dato da speed * 2(sec che voglio che mi riduca per dover arrivare al next)
						obstacle->velocity.y = this->speed;
						obstacle->velocity.x = 0;

						//test
						//obstacle->sprite[0][0].character = '0' + currentId;
						//test
						if (i + obstacle->rect.size.width - 1 < roadWidth - 1) {
							scene->addGameObject(obstacle);
							i += obstacle->rect.size.width - 1;
						}
						else
							delete obstacle;

						placed = true;
					}
				}
			}
			currentId++;
		}
		else if (r < obstacleCumulative + upgradeCumulative) {
			//Genera upgrade
			if (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) {
				bool placed = false;
				for (int j = 1; j <= (sizeof(upgradeProbability) / sizeof(upgradeProbability[0])) && !placed; j++){
					if (r < obstacleCumulative + accumulate(upgradeProbability, upgradeProbability + j, 0.0)) {
						//TODO: define upgrade bonus depeding on type (aka j)
						Upgrade* upgrade = new Upgrade(Point2D(roadPosition + i, 0), this->difficulty * 100, j, this, currentId);
						upgrade->velocity.y = this->speed;
						upgrade->velocity.x = 0;

						//test
						//upgrade->sprite[0][0].character = '0' + currentId;
						//test

						if (i + upgrade->rect.size.width - 1 < roadWidth - 1) {
							scene->addGameObject(upgrade);
							i += upgrade->rect.size.width - 1;
						}
						else
							delete upgrade;						
						
						placed = true;
					}
				}
			}
			currentId++;
		}
		else if (r < obstacleCumulative + upgradeCumulative + AIcarProbability) {
			//Genera AIcar
			if (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) {
				//TODO: make it impossible for aicar to spawn on top of walls
				AICar* aicar = new AICar(Point2D(roadPosition + i, -2), this->difficulty * 50);
				aicar->velocity.y = this->speed * 0.5f;
				aicar->velocity.x = 0;

				//test
				aicar->sprite[1][1].character = '0' + currentId;	//maybe this could be a definitive feature?
				//test
				
				Color centerColor = (Color)(rand() % 15 + 1);
				Color borderColor = (Color)(rand() % 15 + 1);
				for (int y = 0; y < 3; y++) {
					for (int x = 0; x < 3; x++) {
						if (x == 1 && y == 1) {
							aicar->sprite[x][y].foreground = centerColor;
						}
						else {
							aicar->sprite[x][y].foreground = borderColor;
						}
					}
				}
				
				scene->addGameObject(aicar);
			}
			currentId++;
		}
	}
}
