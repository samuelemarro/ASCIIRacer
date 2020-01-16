#include <algorithm>
#include <utility>

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

void GameScene::onStart()
{
	this->gameSpeed = 1;
	PlayerCar* p1 = new PlayerCar(Point2D(30, 27));
	player = p1;
	/*AICar* p2 = new AICar(Point2D(2, 0));
	RoadLine* rl[5];
	for (int i = 0; i < 5; i++) {
		rl[i] = new RoadLine(Point2D(i*7, 0));
		GameScene::addGameObject(rl[i]);
	}
	GameScene::addGameObject(p1);
	GameScene::addGameObject(p2);*/
	//WeirdWall* w = new WeirdWall(Point2D(15, 15), 5);
	//GameScene::addGameObject(w);
	
	GameScene::addGameObject(p1);
	
	//Aggiungi la mappa (ora solo bordi della strada)
	for(int y = -100; y < 20; ++y) {
		Border* border_sx = new Border(Point2D(5, y), 67);
		Border* border_dx = new Border(Point2D(5 + border_sx->roadWidth, y), 23);
		GameScene::addGameObject(border_sx);
		GameScene::addGameObject(border_dx);
	}



	ptr_Level l = new Level(100, -1, 3, 1);  //random level with difficulty 1
	this->currentLevel = l;
	this->nextLevel = NULL;

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

	if (currentLevel->changeLevel(player->points)) {
		this->currentLevel = currentLevel->NextLevel();
	}

	//Inizializzazione dei gameObject
	for (auto gameObject : gameObjects_) {
		if (!gameObject->initialised) {
			gameObject->onStart();
			gameObject->initialised = true;
		}
	}

	for (auto gameObject : gameObjects_) {
		//gameObject->gameSpeed = this->gameSpeed;
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
	Graphics::write(80, 10, "LEVEL: " + std::to_string(currentLevel->difficulty));
	Graphics::write(80, 12, "SCORE: " + std::to_string(player->points));
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

		bool happenedCollision = false;

		for (int x = 0; x < rect.size.width; x++) {
			for (int y = 0; y < rect.size.height; y++) {
				if (gameObjects_[i]->collisionMask[y][x]) {
					int cellX = (int)floor(rect.position.x + (float)x);
					int cellY = (int)floor(rect.position.y + (float)y);

					//Ignora i punti fuori dallo schermo
					if (screenRect.containsPoint(cellX, cellY, true)) {
						if (!collisionBuffer[cellY][cellX].empty()) {
							//Collisione
							happenedCollision = true;
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
