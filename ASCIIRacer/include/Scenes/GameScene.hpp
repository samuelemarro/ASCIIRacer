#pragma once
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"
#include "Levels/Level.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/Road.hpp"


class GameScene : public Scene {
private:
	std::vector<Layer> getLayers();

	PlayerCar* playerCar;
	double roadIndex = 0;
	
	void removeToBeDestroyed();

	std::vector<std::vector<ptr_GameObject>> collisionBuffer;

	void checkCollisions();

public:
	std::vector<ptr_GameObject> gameObjects_;

	ptr_Level currentLevel;

	void onStart() override;
	void onLoop() override;
	void onGraphics() override;
	void onEndLoop() override;

	void addGameObject(ptr_GameObject gameObject);
};