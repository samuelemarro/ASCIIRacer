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

	PlayerCar* p1 = new PlayerCar(Point2D(30, 27), 60);

	this->playerCar = p1;
	this->playerCar->points=0;
	Road* road = new Road(Graphics::screenSize, 5, Graphics::screenSize.height);
	this->road = road;

	this->currentLevel->prepareLevel();


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

	this->popup = new Popup(Point2D(100, 9));
}

void GameScene::onLoop() {

	//Inizializzazione dei gameObject
	for (auto gameObject : getGameObjects()) {
		if (!gameObject->initialised) {
			gameObject->onStart();
			gameObject->initialised = true;
		}
	}

	if (currentLevel->changeLevel(this->playerCar->points)) {
		int oldDifficulty = currentLevel->difficulty;

		this->currentLevel = currentLevel->newLevel(this->playerCar->points);
		this->currentLevel->prepareLevel();

		string directory = System::getExecutableDirectory();

		if (currentLevel->difficulty > oldDifficulty) {
			this->popup->notify(directory + "/sprites/LevelUp.txt", 0.5);
		}
		else {
			this->popup->notify(directory + "/sprites/LevelDown.txt", 0.5);
		}

		if (this->playerCar->points >= 0) {
			for (auto gameObject : getLevelObjects()) {
				gameObject->velocity.y = currentLevel->speed  * ((gameObject->name == "AICar") ? 0.5 : 1);	//put back 0.5 after ?
			}
		}
		else {
			GameEngine::changeScene("GameOverScene");
		}
	}

	/*Aggiorna la velocità
	for (auto levelObject : getLevelObjects()) {
		levelObject->velocity.y = this->currentLevel->speed;    //questo blocco può essere rimosso?
	}*/

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
	//Graphics::write(100, 9, to_string(this->currentLevel->currentId));
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

void GameScene::addToCollisionBuffer(ptr_GameObject gameObject) {
	Size screenSize = Graphics::screenSize;
	Rect screenRect = Rect(Point2D(0, 0), screenSize);

	Point2D velocity = gameObject->velocity;
	Rect rect = gameObject->rect;

	//Simula spostamento
	rect.position.x = (rect.position.x + velocity.x * GameEngine::deltaTime());
	rect.position.y = (rect.position.y + velocity.y * GameEngine::deltaTime());

	if ((rect.position.y + rect.size.height) < this->playerCar->rect.position.y - 1) {
		//Troppo lontano per fare collisioni
		return;
	}

	//Fuori dallo schermo, ignora
	if (rect.position.x + rect.size.width < 0 || rect.position.y + rect.size.height < 0
		|| rect.position.x > screenSize.width || rect.position.y > screenSize.height) {
		return;
	}

	for (int x = 0; x < rect.size.width; x++) {
		for (int y = 0; y < rect.size.height; y++) {
			if (gameObject->sprite[y][x].collision) {
				int cellX = (int)(rect.position.x + (float)x);
				int cellY = (int)(rect.position.y + (float)y);

				//Ignora i punti fuori dallo schermo
				if (screenRect.containsPoint(cellX, cellY, true)) {
					this->collisionBuffer[cellY][cellX] = gameObject;
				}
			}
		}
	}
}

vector<vector<ptr_GameObject>> GameScene::getCollisionMatrix(ptr_GameObject gameObject, bool future) {
	Size screenSize = Graphics::screenSize;
	Rect screenRect = Rect(Point2D(0, 0), screenSize);

	int positionX;
	int positionY;

	if (future) {
		positionX = (int)(gameObject->futurePosition().x);
		positionY = (int)(gameObject->futurePosition().y);
	}
	else {
		positionX = (int)(gameObject->rect.position.x);
		positionY = (int)(gameObject->rect.position.y);
	}

	vector<vector<ptr_GameObject>> collisionMatrix;
	collisionMatrix.reserve(gameObject->rect.size.height);

	for (int y = 0; y < gameObject->rect.size.height; y++) {
		vector<ptr_GameObject> row;
		row.reserve(gameObject->rect.size.width);

		for (int x = 0; x < gameObject->rect.size.width; x++) {
			int cellX = x + positionX;
			int cellY = y + positionY;

			if (screenRect.containsPoint(cellX, cellY, true) && gameObject->sprite[y][x].collision
				&& collisionBuffer[cellY][cellX] != NULL) {
				ptr_GameObject collider = collisionBuffer[cellY][cellX];
				row.push_back(collider);
			}
			else {
				row.push_back(NULL);
			}
		}

		collisionMatrix.push_back(row);
	}

	return collisionMatrix;
}

std::vector<std::pair<ptr_GameObject, CollisionType>> GameScene::getCollisionPairs(ptr_GameObject gameObject, bool future)
{
	vector<vector<ptr_GameObject>> collisionMatrix = getCollisionMatrix(gameObject, future);

	vector<std::pair<ptr_GameObject, CollisionType>> pairs;

	//Primo passo: Identifica tutti i collider
	for (auto row : collisionMatrix) {
		for (ptr_GameObject collider : row) {
			bool alreadyAdded = false;
			for (auto pair : pairs) {
				if (pair.first == collider) {
					alreadyAdded = true;
				}
			}

			if (!alreadyAdded && collider != NULL) {
				pairs.push_back(pair<ptr_GameObject, CollisionType>(collider, CollisionType()));
			}
		}
	}

	Size size = gameObject->rect.size;

	//Secondo passo: Classifica i collider
	for (int i = 0; i < pairs.size(); i++) {
		ptr_GameObject collider = pairs[i].first;

		//Any
		for (int x = 0; x < size.width; x++) {
			for (int y = 0; y < size.height; y++) {
				if (collisionMatrix[y][x] == collider) {
					pairs[i].second.any = true;
				}
			}
		}

		//Top e bottom
		for (int x = 0; x < size.width; x++) {
			if (collisionMatrix[0][x] == collider) {
				pairs[i].second.top = true;
			}

			if (collisionMatrix[size.height - 1][x] == collider) {
				pairs[i].second.bottom = true;
			}
		}

		//Left e right
		for (int y = 0; y < size.height; y++) {
			if (collisionMatrix[y][0] == collider) {
				pairs[i].second.left = true;
			}

			if (collisionMatrix[y][size.width - 1] == collider) {
				pairs[i].second.right = true;
			}
		}
	}

	return pairs;
}

std::vector<CollisionInfo> GameScene::getCollisionInfos(ptr_GameObject gameObject)
{
	vector<pair<ptr_GameObject, CollisionType>> presentPairs = getCollisionPairs(gameObject, false);
	vector<pair<ptr_GameObject, CollisionType>> futurePairs;

	if (gameObject->velocity.magnitude() == 0) {
		futurePairs = presentPairs;
	}
	else {
		futurePairs = getCollisionPairs(gameObject, true);
	}

	vector<CollisionInfo> collisionInfos;

	//Fai corrispondere le CollisionType dei present e dei future

	for (auto futurePair : futurePairs) {
		CollisionType present;

		for (auto presentPair : presentPairs) {
			if (presentPair.first == futurePair.first) {
				present = presentPair.second;
			}
		}

		collisionInfos.push_back(CollisionInfo(futurePair.first, present, futurePair.second));
	}

	for (auto presentPair : presentPairs) {
		bool alreadyAdded = false;
		for (CollisionInfo collisionInfo : collisionInfos) {
			if (collisionInfo.collider == presentPair.first) {
				alreadyAdded = true;
			}
		}

		if (!alreadyAdded) {
			collisionInfos.push_back(CollisionInfo(presentPair.first, presentPair.second, CollisionType()));
		}
	}

	return collisionInfos;
}

void GameScene::checkCollisions()
{
	Size screenSize = Graphics::screenSize;

	//Pulisci il buffer
	for (int i = 0; i < screenSize.height; i++) {
		for (int j = 0; j < screenSize.width; j++) {
			collisionBuffer[i][j] = NULL;
		}
	}

	//Prima fase: oggetti che non richiedono controlli collisione
	for (ptr_GameObject gameObject : getLevelObjects()) {
		if (gameObject->name != "AICar") {
			addToCollisionBuffer(gameObject);
		}
	}

	for (ptr_GameObject gameObject : getLevelObjects()) {
		if (gameObject->name == "AICar") {
			for (auto collisionInfo : getCollisionInfos(gameObject)) {
				((AICar*)gameObject)->onCollision(collisionInfo);
			}
			addToCollisionBuffer(gameObject);
		}
	}

	//Informa l'automobile delle collisioni
	for (auto collisionInfo : getCollisionInfos(this->playerCar)) {
		this->playerCar->onCollision(collisionInfo);
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
	if (this->popup != NULL) {
		allGameObjects.push_back(this->popup);
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

void GameScene::increasePoints() {
	this->tilesCount += 1;    //tiene il conto dei quadretti percorsi dall'ultimo increase di punti dovuti all'andare avanti
	
	//ogni 10 quadretti mi dà 1 punto
	if (tilesCount % 10 == 0) {
		//this->playerCar->points += 1;
		this->tilesCount = 0;
	}
}