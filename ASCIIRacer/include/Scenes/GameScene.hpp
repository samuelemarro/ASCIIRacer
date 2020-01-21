#pragma once
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"
#include "Levels/Level.hpp"
#include "GameObjects/GeneratedObject.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/Road.hpp"


class GameScene : public Scene {
private:
	std::vector<Layer> getLayers();

	PlayerCar* playerCar;
	double roadIndex = 0;
	Road* road;
	vector<ptr_GeneratedObject> otherObjects;
	
	void removeToBeDestroyed();

	std::vector<std::vector<ptr_GameObject>> collisionBuffer;

	void checkCollisions();

	vector<ptr_GameObject> getGameObjects();
	std::vector<ptr_GameObject> getLevelObjects();

public:

	ptr_Level currentLevel;

	~GameScene();
	void onStart() override;
	void onLoop() override;
	void onGraphics() override;
	void onEndLoop() override;

	void addGameObject(ptr_GeneratedObject gameObject);
};