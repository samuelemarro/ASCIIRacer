#include <algorithm>
#include <utility>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>  

#include "Scenes/GameScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"
#include "Core/Utilities.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/LevelObjects/AICar.hpp"
#include "GameObjects/LevelObjects/WeirdWall.hpp"
#include "GameObjects/LevelObjects/RoadLine.hpp"
#include "GameObjects/LevelObjects/Border.hpp"
#include "GameObjects/LevelObjects/Obstacle.hpp"
#include "GameObjects/LevelObjects/Upgrade.hpp"
#include "Levels/Level.hpp"

using std::max;
using std::min;
using std::pair;
using std::vector;
using std::sort;
PlayerCar* player;
int roadX = 10;

void GameScene::onStart()
{
	ptr_Level l = new Level(100, -1, 1, 1, 70, 5);  //random level with difficulty 1
	this->currentLevel = l;
	this->nextLevel = NULL;

	this->gameSpeed = 1;
	srand(time(NULL));
	PlayerCar* p1 = new PlayerCar(Point2D(30, 27));
	player = p1;
	AICar* p2 = new AICar(Point2D(2, 0));
	
	GameScene::addGameObject(p1);
	
	for (int i = 0; i < 30; i++) {
		RoadLine* rl = new RoadLine(Point2D(roadX, i), 'n');
		GameScene::addGameObject(rl);
	}
	//GameScene::addGameObject(p2);
	Upgrade* upgrade = new Upgrade(Point2D(25, -10), 250);  //random upgrade with 250 points as bonus
	GameScene::addGameObject(upgrade);

	Obstacle* obstacle = new Obstacle(Point2D(25, -15), 250);  //random upgrade with 250 points as bonus
	GameScene::addGameObject(obstacle);

	this->gameSpeed = currentLevel->speed;

	//Prepara il collisionBuffer
	Size screenSize = Graphics::screenSize;
	collisionBuffer.reserve(screenSize.height);

	for (int i = 0; i < screenSize.height; i++) {
		vector<vector<int>> row = vector<vector<int>>();
		row.reserve(screenSize.width);
		for (int j = 0; j < screenSize.width; j++) {
			vector<int> collisions = vector<int>();
			row.push_back(collisions);
		}
		collisionBuffer.push_back(row);
	}
}

void GameScene::onLoop() {

	if (Graphics::buffer[0][roadX] == ' ') {
		int k = rand() % 5;
		char c = 'n';
		if (k == 0 && roadX > 0) { c = 's'; roadX--; }
		else if (k != 0 && k != 2) c = 'n';
		else if (k == 2 && roadX < 40) c = 'd';
		RoadLine* rl = new RoadLine(Point2D(roadX, 0), c);
		GameScene::addGameObject(rl);
		if (roadX < 40 && c == 'd') roadX++;
	}

	if (currentLevel->changeLevel(player->points)) {
		this->currentLevel = currentLevel->NextLevel(player->points);
	}
	//Inizializzazione dei gameObject
	for (auto gameObject : gameObjects_) {
		if (!gameObject->initialised) {
			gameObject->onStart();
			gameObject->initialised = true;
		}
	}

	for (auto gameObject : gameObjects_) {
		gameObject->gameSpeed = this->gameSpeed;
		gameObject->onUpdate();
	}

	checkCollisions();
	for (auto GameObject : gameObjects_) {
		GameObject->rect.position.x += GameObject->velocity.x * GameEngine::deltaTime();
		GameObject->rect.position.y += GameObject->velocity.y * GameEngine::deltaTime();
	}
}

void GameScene::onGraphics()
{
	Graphics::write(100, 5, "LEVEL: " + std::to_string(currentLevel->difficulty));
	Graphics::write(100, 7, "SCORE: " + std::to_string(player->points));
	for (Layer layer : getLayers()) {
		for (auto gameObject : gameObjects_) {
			if (gameObject->layer == layer) {
				Graphics::draw(gameObject);
			}
		}
	}
}

void GameScene::onEndLoop()
{
	//Finalizzazione
	removeToBeDestroyed();
}

void GameScene::removeToBeDestroyed()
{
	//Rimuovi i GameObject da distruggere
	for (int i = 0; i < gameObjects_.size(); i++) {
		if (gameObjects_[i]->toBeDestroyed) {
			delete gameObjects_[i];
			gameObjects_.erase(gameObjects_.begin() + i);
			i--;
		}
	}
}

void GameScene::checkCollisions()
{
	Size screenSize = Graphics::screenSize;
	Rect screenRect = Rect(Point2D(0, 0), screenSize);

	//Pulisci il buffer
	for (int i = 0; i < screenSize.height; i++) {
		for (int j = 0; j < screenSize.width; j++) {
			collisionBuffer[i][j].clear();
		}
	}

	vector<pair<int, int>> collisions = vector<pair<int, int>>();

	for (int i = 0; i < gameObjects_.size(); i++) {
		Point2D velocity = gameObjects_[i]->velocity;
		Rect rect = gameObjects_[i]->rect;

		//Simula spostamento
		rect.position.x = floor(rect.position.x + velocity.x * GameEngine::deltaTime());
		rect.position.y = floor(rect.position.y + velocity.y * GameEngine::deltaTime());

		//Fuori dallo schermo, ignora
		if (rect.position.x + rect.size.width < 0 || rect.position.y + rect.size.height < 0
			|| rect.position.x > screenSize.width || rect.position.y > screenSize.height) {
			continue;
		}

		for (int x = 0; x < rect.size.width; x++) {
			for (int y = 0; y < rect.size.height; y++) {
				if (gameObjects_[i]->collisionMask[y][x]) {
					int cellX = (int)floor(rect.position.x + (float)x);
					int cellY = (int)floor(rect.position.y + (float)y);

					//Ignora i punti fuori dallo schermo
					if (screenRect.containsPoint(cellX, cellY, true)) {
						if (!collisionBuffer[cellY][cellX].empty()) {
							//Collisione
							for (int other : collisionBuffer[cellY][cellX]) {
								int first = min(i, other);
								int second = max(i, other);

								pair<int, int> collision = pair<int, int>(first, second);

								if (find(collisions.begin(), collisions.end(), collision) == collisions.end()) {
									collisions.push_back(collision);
								}
							}
						}
						collisionBuffer[cellY][cellX].push_back(i);
					}
				}
			}
		}
	}

	//Informa gli oggetti delle collisioni e ferma gli oggetti
	//non immovibili
	for (auto collision : collisions) {
		ptr_GameObject first = gameObjects_[collision.first];
		ptr_GameObject second = gameObjects_[collision.second];

		if (!first->immovable) {
			first->velocity = Point2D(0, 0);
		}
		if (!second->immovable) {
			second->velocity = Point2D(0, 0);
		}

		first->onCollision(second);
		second->onCollision(first);
	}
}

vector<Layer> GameScene::getLayers()
{
	vector<Layer> layers;

	for (auto gameObject : gameObjects_) {
		if (find(layers.begin(), layers.end(), gameObject->layer) == layers.end()) {
			layers.push_back(gameObject->layer);
		}
	}

	sort(layers.begin(), layers.end());

	return layers;
}

void GameScene::addGameObject(ptr_GameObject gameObject) {
	gameObjects_.push_back(gameObject);
}
