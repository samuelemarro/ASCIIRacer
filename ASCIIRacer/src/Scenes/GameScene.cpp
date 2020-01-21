#include <algorithm>
#include <utility>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>  

#include "Scenes/GameScene.hpp"
#include "Scenes/GameOverScene.hpp"
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
#include "GameObjects/Road.hpp"

using std::max;
using std::min;
using std::pair;
using std::vector;
using std::sort;

void GameScene::onStart()
{
	srand(time(NULL));

	ptr_Level l = new Level(100, -1, 3, 1);  //initial level with difficulty 1
	this->currentLevel = l;

	PlayerCar* p1 = new PlayerCar(Point2D(30, 27));
	AICar* p2 = new AICar(Point2D(2, 0));

	this->playerCar = p1;
	this->playerCar->points=0;
	Road* road = new Road(Graphics::screenSize, 5, Graphics::screenSize.height);
	GameScene::addGameObject(road);
	Obstacle* o = new Obstacle(Point2D(30, 10), 1000);
	GameScene::addGameObject(o);
	for (auto gameObject : gameObjects_) {
		gameObject->velocity.y = currentLevel->speed;
	}

	//Prepara il collisionBuffer
	Size screenSize = Graphics::screenSize;
	collisionBuffer.reserve(screenSize.height);

	for (int i = 0; i < screenSize.height; i++) {
		vector<ptr_GameObject> row = vector<ptr_GameObject>();
		row.reserve(screenSize.width);
		for (int j = 0; j < screenSize.width; j++) {
			row.push_back(NULL);
		}
		collisionBuffer.push_back(row);
	}
}

void GameScene::onLoop() {

	//allGameObjects include anche l'automobile
	vector<ptr_GameObject> allGameObjects = gameObjects_;
	allGameObjects.push_back(this->playerCar);

	//Inizializzazione dei gameObject
	for (auto gameObject : allGameObjects) {
		if (!gameObject->initialised) {
			gameObject->onStart();
			gameObject->initialised = true;
		}
	}

	//playerCar->points += 5;
	if (currentLevel->changeLevel(this->playerCar->points)) {
		this->currentLevel = currentLevel->NextLevel(this->playerCar->points);
		for (auto gameObject : gameObjects_) {
			if(this->playerCar->points>=0) gameObject->velocity.y = currentLevel->speed;
			else {
				ptr_Scene p = new GameOverScene();
				GameEngine::changeScene(p);
			}
		}
	}

	int old_roadIndex = this->roadIndex;
	this->roadIndex += (int)(currentLevel->speed) * GameEngine::deltaTime();

	if (old_roadIndex != (int)(this->roadIndex)) {
		this->playerCar->points += 5 * (int)(this->roadIndex - old_roadIndex);

		if (gameObjects_[0]->name == "Road") {
			gameObjects_[0]->onUpdate();
		} else {
			Graphics::write(100, 9, "ERROR: Road");
		}

		//generate new line of map
		bool generateMap = (old_roadIndex % 29 == 0);
		vector<ptr_GameObject> levelObjects = currentLevel->getMapLine(this->roadIndex, gameObjects_[0], generateMap);
		for (auto levelObject : levelObjects) {
			gameObjects_.push_back(levelObject);
		}
	}

	for (auto gameObject : allGameObjects) {
		if(gameObject->name != "Road") gameObject->onUpdate();
	}

	checkCollisions();
	for (auto GameObject : allGameObjects) {
		GameObject->rect.position.x += GameObject->velocity.x * GameEngine::deltaTime();
		GameObject->rect.position.y += GameObject->velocity.y * GameEngine::deltaTime();
	}
}

void GameScene::onGraphics()
{
	//allGameObjects include anche l'automobile
	vector<ptr_GameObject> allGameObjects = gameObjects_;
	allGameObjects.push_back(this->playerCar);

	Graphics::write(100, 5, "LEVEL: " + std::to_string(currentLevel->difficulty));
	if(this->playerCar->points >= 0)Graphics::write(100, 7, "SCORE: " + std::to_string(this->playerCar->points));
	else {
		ptr_Scene p = new GameOverScene();
		GameEngine::changeScene(p);
	}
	//test printing
	Graphics::write(100, 9, "TEST: " + std::to_string((int)(roadIndex)));
	//test printing
	for (Layer layer : getLayers()) {
		for (auto gameObject : allGameObjects) {
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
			collisionBuffer[i][j] = NULL;
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
				if (gameObjects_[i]->sprite[y][x].collision) {
					int cellX = (int)floor(rect.position.x + (float)x);
					int cellY = (int)floor(rect.position.y + (float)y);

					//Ignora i punti fuori dallo schermo
					if (screenRect.containsPoint(cellX, cellY, true)) {
						collisionBuffer[cellY][cellX] = gameObjects_[i];
					}
				}
			}
		}
	}

	//Collisione con spostamento e senza spostamento = collisione verticale
	//Collisione con spostamento = collisione orizzontale
	//Collisione senza spostamento = nessuna collisione (l'ha schivato)

	vector<ptr_GameObject> colliders = vector<ptr_GameObject>();
	vector<ptr_GameObject> staticColliders = vector<ptr_GameObject>();

	//La posizione verticale dell'auto non cambia
	int carPosY = (int)floor(this->playerCar->rect.position.y);

	//Primo controllo collisioni: Usa la posizione futura (quella che avrà se si muove)
	Point2D futureCarPosition = this->playerCar->futurePosition();
	int futurePosX = (int)floor(futureCarPosition.x);
	
	for (int y = 0; y < this->playerCar->rect.size.height; y++) {
		for (int x = 0; x < this->playerCar->rect.size.width; x++) {
			int cellX = x + futurePosX;
			int cellY = y + carPosY;

			if (screenRect.containsPoint(cellX, cellY, true)) {
				if (this->playerCar->sprite[y][x].collision && collisionBuffer[cellY][cellX] != NULL) {
					ptr_GameObject collider = collisionBuffer[cellY][cellX];
					if (find(colliders.begin(), colliders.end(), collider) == colliders.end()) {
						colliders.push_back(collider);
					}
				}
			}
		}
	}

	if (colliders.size() > 0) {
		//Secondo controllo collisioni: Usa la posizione statica
		int staticPosX = (int)floor(this->playerCar->rect.position.x);

		for (int y = 0; y < this->playerCar->rect.size.height; y++) {
			for (int x = 0; x < this->playerCar->rect.size.width; x++) {
				int cellX = x + staticPosX;
				int cellY = y + carPosY;

				if (screenRect.containsPoint(cellX, cellY, true)) {
					if (this->playerCar->sprite[y][x].collision && collisionBuffer[cellY][cellX] != NULL) {
						ptr_GameObject collider = collisionBuffer[cellY][cellX];

						//Conta come collisione solo se c'è stata anche la collisione con la posizione futura
						if (find(colliders.begin(), colliders.end(), collider) != colliders.end() &&
							find(staticColliders.begin(), staticColliders.end(), collider) == staticColliders.end()) {
							staticColliders.push_back(collider);
						}
					}
				}
			}
		}
	}

	//Informa l'automobile delle collisioni
	for (auto collider : colliders) {
		bool horizontal = (find(staticColliders.begin(), staticColliders.end(), collider) == staticColliders.end());
		this->playerCar->onCollision(collider, horizontal);
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