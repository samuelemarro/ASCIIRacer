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

using std::max;
using std::min;
using std::pair;
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
	WeirdWall* w = new WeirdWall(Point2D(15, 15), 5);
	GameScene::addGameObject(w);
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
		//gameObject->gameSpeed = this->gameSpeed;
		gameObject->onUpdate();
	}

	for (auto physicalObject : physicalObjects_) {
		checkCollisions();
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

void GameScene::checkCollisions()
{
	float correctionFactor = 0;
	float movingThreshold = 0.01;
	//Nota: Far ripetere tutto alla fine

	Size screenSize = System::getConsoleSize();

	vector<pair<int, int>> collisions = vector<pair<int, int>>();

	for (auto layer : getCollisionLayers()) {
		bool performedCorrections = true;

		while (performedCorrections) {
			performedCorrections = false;

			//Segna i blocchi lentissimi come fermi
			for (auto physicalObject : physicalObjects_) {
				if (physicalObject->velocity.magnitude() < movingThreshold) {
					physicalObject->velocity = Point2D(0, 0);
				}
			}

			for (int y = 0; y < screenSize.height; y++) {
				for (int x = 0; x < screenSize.width; x++) {
					//Identifica i conflitti
					vector<int> conflicting = vector<int>();

					for (int i = 0; i < physicalObjects_.size(); i++) {
						auto physicalObject = physicalObjects_[i];

						if (physicalObject->collisionLayer != layer) {
							continue;
						}

						Size size = physicalObject->rect.size;

						//Simula uno spostamento
						int posX = (int)round(physicalObject->rect.position.x + physicalObject->velocity.x * GameEngine::deltaTime());
						int posY = (int)round(physicalObject->rect.position.y + physicalObject->velocity.y * GameEngine::deltaTime());
						Point2D newPosition = Point2D(posX, posY);

						Rect newRect = Rect(newPosition, size);

						int spritePosX = x - posX;
						int spritePosY = y - posY;

						if (newRect.containsPoint(x, y, true)) {
							if (physicalObject->collisionMask[spritePosY][spritePosX]) {
								conflicting.push_back(i);
							}
						}
					}

					//Se ci sono state collisioni
					if (conflicting.size() >= 2) {

						//Segna tutte le collisioni
						for (int i = 0; i < conflicting.size(); i++) {
							for (int j = 0; j < conflicting.size(); j++) {
								if (i != j) {
									auto collision = pair<int, int>(min(i, j), max(i, j));
									if (find(collisions.begin(), collisions.end(), collision) == collisions.end()) {
										collisions.push_back(collision);
									}
								}
							}
						}


						//Controlla che non siano tutti oggetti immovibili o fermi
						bool allUnfixable = true;
						for (auto index : conflicting) {
							auto physicalObject = physicalObjects_[index];
							if (!physicalObject->immovable && physicalObject->velocity.magnitude() != 0) {
								allUnfixable = false;
							}
						}

						if (!allUnfixable) {
							performedCorrections = true;
							//Riduci la velocit� degli oggetti che hanno avuto una collisione
							for (auto index : conflicting) {
								auto physicalObject = physicalObjects_[index];
								if (!physicalObject->immovable && physicalObject->velocity.magnitude() != 0) {
									physicalObject->velocity.x *= correctionFactor;
									physicalObject->velocity.y *= correctionFactor;
								}

							}
						}
					}
				}
			}
		}
	}

	//Informa gli oggetti delle collisioni
	for (auto collision : collisions) {
		ptr_PhysicalObject first = physicalObjects_[collision.first];
		ptr_PhysicalObject second = physicalObjects_[collision.second];

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

std::vector<Layer> GameScene::getCollisionLayers()
{
	vector<Layer> layers;

	for (auto physicalObject : physicalObjects_) {
		if (find(layers.begin(), layers.end(), physicalObject->collisionLayer) == layers.end()) {
			layers.push_back(physicalObject->collisionLayer);
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