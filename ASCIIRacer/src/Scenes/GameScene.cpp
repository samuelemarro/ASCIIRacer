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

	ptr_Level l = new Level(100, -1, 10, 1);  //initial level with difficulty 1
	this->currentLevel = l;

	PlayerCar* p1 = new PlayerCar(Point2D(30, 27));
	AICar* p2 = new AICar(Point2D(2, 0));

	this->playerCar = p1;
	this->playerCar->points=0;
	Road* road = new Road(Graphics::screenSize, 5, Graphics::screenSize.height);
	this->road = road;
	//Obstacle* o = new Obstacle(Point2D(30, 10), 1000);
	//GameScene::addGameObject(o);

	for (auto gameObject : getLevelObjects()) {
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

	//Inizializzazione dei gameObject
	for (auto gameObject : getGameObjects()) {
		if (!gameObject->initialised) {
			gameObject->onStart();
			gameObject->initialised = true;
		}
	}

	//playerCar->points += 5;
	if (currentLevel->changeLevel(this->playerCar->points)) {
		this->currentLevel = currentLevel->newLevel(this->playerCar->points);
		this->currentLevel->prepareLevel();

		if (this->playerCar->points >= 0) {
			for (auto gameObject : getLevelObjects()) {
				gameObject->velocity.y = currentLevel->speed;

			}
		}
		else {
			GameEngine::changeScene("GameOverScene");
		}
	}

	//Aggiorna la velocità
	for (auto levelObject : getLevelObjects()) {
		levelObject->velocity.y = this->currentLevel->speed;
	}

	for (auto gameObject : getGameObjects()) {
		gameObject->onUpdate();
	}

	checkCollisions();
	for (auto GameObject : getGameObjects()) {
		GameObject->rect.position.x += GameObject->velocity.x * GameEngine::deltaTime();
		GameObject->rect.position.y += GameObject->velocity.y * GameEngine::deltaTime();
	}
}

void GameScene::onGraphics()
{

	Graphics::write(100, 5, "LEVEL: " + std::to_string(currentLevel->difficulty));
	if (this->playerCar->points >= 0)Graphics::write(100, 7, "SCORE: " + std::to_string(this->playerCar->points));
	else GameEngine::changeScene("GameOverScene");
	//test printing
	Graphics::write(100, 9, "TEST: " + std::to_string(getGameObjects().size()));
	//test printing
	for (Layer layer : getLayers()) {
		for (auto gameObject : getGameObjects()) {
			if (gameObject->layer == layer) {
				Graphics::draw(gameObject);
			}
		}
	}
}

void GameScene::onEndLoop()
{
	for (auto gameObject : getGameObjects()) {
		if (gameObject->rect.position.y > Graphics::screenSize.height) {
			gameObject->toBeDestroyed = true;
		}
	}

	//Finalizzazione
	removeToBeDestroyed();
}

void GameScene::removeToBeDestroyed()
{
	//Rimuovi i GameObject da distruggere
	for (int i = 0; i < otherObjects.size(); i++) {
		if (otherObjects[i]->toBeDestroyed) {
			delete otherObjects[i];
			otherObjects.erase(otherObjects.begin() + i);
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


	for (ptr_GameObject levelObject : getLevelObjects()) {
		Point2D velocity = levelObject->velocity;
		Rect rect = levelObject->rect;

		//Simula spostamento
		rect.position.x = floor(rect.position.x + velocity.x * GameEngine::deltaTime());
		rect.position.y = floor(rect.position.y + velocity.y * GameEngine::deltaTime());

		if (floor(rect.position.y + rect.size.height) < this->playerCar->rect.position.y - 1) {
			//Troppo lontano per fare collisioni
			continue;
		}

		//Fuori dallo schermo, ignora
		if (rect.position.x + rect.size.width < 0 || rect.position.y + rect.size.height < 0
			|| rect.position.x > screenSize.width || rect.position.y > screenSize.height) {
			continue;
		}

		for (int x = 0; x < rect.size.width; x++) {
			for (int y = 0; y < rect.size.height; y++) {
				if (levelObject->sprite[y][x].collision) {
					int cellX = (int)floor(rect.position.x + (float)x);
					int cellY = (int)floor(rect.position.y + (float)y);

					//Ignora i punti fuori dallo schermo
					if (screenRect.containsPoint(cellX, cellY, true)) {
						collisionBuffer[cellY][cellX] = levelObject;
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

vector<ptr_GameObject> GameScene::getGameObjects()
{
	vector<ptr_GameObject> allGameObjects(this->otherObjects.begin(), this->otherObjects.end());
	if (this->road != NULL) {
		allGameObjects.push_back(this->road);
	}
	if (this->playerCar != NULL) {
		allGameObjects.push_back(this->playerCar);
	}

	return allGameObjects;
}

std::vector<ptr_GameObject> GameScene::getLevelObjects()
{
	vector<ptr_GameObject> collisionGameObjects(this->otherObjects.begin(), this->otherObjects.end());
	if (this->road != NULL) {
		collisionGameObjects.push_back(this->road);
	}

	return collisionGameObjects;
}


vector<Layer> GameScene::getLayers()
{
	vector<Layer> layers;

	for (auto gameObject : getGameObjects()) {
		if (find(layers.begin(), layers.end(), gameObject->layer) == layers.end()) {
			layers.push_back(gameObject->layer);
		}
	}

	sort(layers.begin(), layers.end());

	return layers;
}

void GameScene::addGameObject(ptr_GeneratedObject gameObject) {
	this->otherObjects.push_back(gameObject);
}

GameScene::~GameScene() {
	this->initialised = false;
	this->collisionBuffer.erase(this->collisionBuffer.begin(), this->collisionBuffer.end());
	delete this->currentLevel;
	this->otherObjects.erase(this->otherObjects.begin(), this->otherObjects.end());
	delete this->nextScene;
	delete this->playerCar;
	this->roadIndex = 0;
}