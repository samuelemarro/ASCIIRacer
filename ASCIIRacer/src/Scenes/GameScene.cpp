#include <algorithm>

#include "Scenes/GameScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/LevelObjects/AICar.hpp"

using std::vector;
using std::sort;
PlayerCar* player;

void GameScene::onStart()
{
	this->gameSpeed = 1;
	PlayerCar* p1 = new PlayerCar(Point2D(1, 27));
	player = p1;
	AICar* p2 = new AICar(Point2D(1, 0));
	GameScene::addGameObject(p1);
	GameScene::addGameObject(p2);
}

void GameScene::onLoop() {
	
	this->gameSpeed = pow(1.2, player->level);

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

	for (auto physicalObject : physicalObjects_) {
		//TODO: Controllo collisioni
		physicalObject->rect.position.x += physicalObject->velocity.x * GameEngine::deltaTime();
		physicalObject->rect.position.y += physicalObject->velocity.y * GameEngine::deltaTime();
	}
}

void GameScene::onGraphics()
{
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
	//Rimuovi i PhysicalObject da distruggere (senza eliminare)
	for (int i = 0; i < physicalObjects_.size(); i++) {
		if (physicalObjects_[i]->toBeDestroyed) {
			physicalObjects_.erase(physicalObjects_.begin() + i);
			i--;
		}
	}

	//Rimuovi i GameObject da distruggere (eliminando)
	for (int i = 0; i < gameObjects_.size(); i++) {
		if (gameObjects_[i]->toBeDestroyed) {
			delete gameObjects_[i];
			gameObjects_.erase(gameObjects_.begin() + i);
			i--;
		}
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

void GameScene::addGameObject(ptr_PhysicalObject physicalObject) {
	gameObjects_.push_back(physicalObject);
	physicalObjects_.push_back(physicalObject);
}