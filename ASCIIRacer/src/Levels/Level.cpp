#include "Levels/Level.hpp"
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

	for (int i = 0; i < 3); ++i)
		obstacleProbability[i] = min(obstacleProbability[i] + (this->difficulty - 1) * 0.0001, obstacleProbability[i] / 6 * 10);
	obstacleCumulative = accumulate(obstacleProbability, obstacleProbability + 3), 0.0);

	for (int i = 0; i < 2); ++i)
		upgradeProbability[i] = max(upgradeProbability[i] - (this->difficulty - 1) * 0.0001, 0.0);
	upgradeCumulative = accumulate(upgradeProbability, upgradeProbability + 2), 0.0);

	AIcarProbability = min(0.0005 + 0.0001 * (this->difficulty / 2), 0.0010);
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
			Level* new_level = new Level(pointsToNextLevel + 1000, pointsToNextLevel - 100, min(speed + 1, 30), difficulty + 1);
			this->nextLevel = new_level;
			new_level->prevLevel = this;
			new_level->nextLevel = NULL;
			return new_level;
		}
		else
			return this->nextLevel;
	}

	else if (player_points <= this->pointsToPrevLevel) {
		return this->prevLevel;
	}

	else return this;		//Caso mai raggiunto poichè precondition: changeLevel == true
}



void Level::generateLine(int roadPosition, int roadWidth) {

	GameScene* scene = (GameScene*)GameEngine::currentScene;
	
	for (int i = 1; i < roadWidth; i++) {
		float r = System::randomFloat();

		if (r < obstacleCumulative) {
			//Genera ostacolo
			bool placed = false;
			for (int j = 1; j <= 3) && !placed; j++) {
				if (r < accumulate(obstacleProbability, obstacleProbability + j, 0.0)) {
					Obstacle* obstacle = new Obstacle(Point2D(roadPosition + i, 0), min(150 + 75 * (3 - j) + 25 * (this->difficulty - 1), 250 + 125 * (3 - j)), j, this, currentId);
					obstacle->velocity.y = this->speed;
					obstacle->velocity.x = 0;

					i += obstacle->rect.size.width - 1;

					if ( (i < roadWidth) && (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) )
						scene->addGameObject(obstacle);
					else
						delete obstacle;

					placed = true;

					//se era un muro, crea anche fino ad altri 3 muri alla sua destra
					if (j == 3) {
						for (int k = 0; k < 4; k++) {
							currentId++;
							Obstacle* obstacle = new Obstacle(Point2D(roadPosition + i, 0), min(150 + 75 * (3 - j) + 25 * (this->difficulty - 1), 250 + 125 * (3 - j)), j, this, currentId);
							obstacle->velocity.y = this->speed;
							obstacle->velocity.x = 0;

							i += obstacle->rect.size.width - 1;
							if ((i < roadWidth) && (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()))
								scene->addGameObject(obstacle);
							else
								delete obstacle;

							i++;
						}
					}
				}
			}
			currentId++;
		}
		else if (r < obstacleCumulative + upgradeCumulative) {
			//Genera upgrade
			bool placed = false;
			for (int j = 1; j <= 2) && !placed; j++){
				if (r < obstacleCumulative + accumulate(upgradeProbability, upgradeProbability + j, 0.0)) {
					Upgrade* upgrade = new Upgrade(Point2D(roadPosition + i, 0), 150 + 150 * (j - 1), j, this, currentId);
					upgrade->velocity.y = this->speed;
					upgrade->velocity.x = 0;

					i += upgrade->rect.size.width - 1;

					if ( (i < roadWidth) && (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) )
						scene->addGameObject(upgrade);
					else
						delete upgrade;						
						
					placed = true;
				}
			}
			currentId++;
		}
		else if (r < obstacleCumulative + upgradeCumulative + AIcarProbability) {
			//Genera AIcar
			if (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()) {
				AICar* aicar = new AICar(Point2D(roadPosition + i, -2), min(500 + 50 * (this->difficulty - 1), 1000));
				aicar->velocity.y = this->speed * 0.5f;
				aicar->velocity.x = (rand() % 6) * ((i <= roadWidth/2) ? 1.0f : -1.0f);

				aicar->sprite[1][1].character = '0' + rand() % 10;	
				
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
				
				i += aicar->rect.size.width - 1;

				if (i < roadWidth)
					scene->addGameObject(aicar);
				else
					delete aicar;
			}
			currentId++;
		}
	}
}
