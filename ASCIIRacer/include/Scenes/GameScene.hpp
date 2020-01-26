#pragma once
#include "Core/CollisionInfo.hpp"
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"
#include "Levels/Level.hpp"
#include "GameObjects/GeneratedObject.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/Popup.hpp"
#include "GameObjects/Road.hpp"

class GameScene : public Scene {
private:
	std::vector<Layer> getLayers();

	PlayerCar* playerCar;
	double travelBonus = 0;
	Road* road;
	vector<ptr_GeneratedObject> otherObjects;

	float bestScore;

	ptr_Popup popup;

	void removeToBeDestroyed();

	std::vector<std::vector<ptr_GameObject>> collisionBuffer;

	void addToCollisionBuffer(ptr_GameObject gameObject);
	vector<vector<ptr_GameObject>> getCollisionMatrix(ptr_GameObject gameObject, bool future);
	std::vector<std::pair<ptr_GameObject, CollisionType>> getCollisionPairs(ptr_GameObject gameObject, bool future);
	std::vector<CollisionInfo> getCollisionInfos(ptr_GameObject gameObject);
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

	void increasePoints();
	void addGameObject(ptr_GeneratedObject gameObject);
};