#include <algorithm>

#include "Scenes/GameScene.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"

using std::vector;
using std::sort;

void GameScene::onStart()
{
	PlayerCar* p = new PlayerCar(Point2D(10, 10));
	GameScene::addGameObject(p);
}

void GameScene::onLoop() {
	//Inizializzazione dei gameObject
	for (auto gameObject : gameObjects_) {
		if (!gameObject->initialised) {
			gameObject->onStart();
			gameObject->initialised = true;
		}
	}

	for (auto gameObject : gameObjects_) {
		gameObject->onUpdate();
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