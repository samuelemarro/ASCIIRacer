#pragma once
#include "GameObjects/GameObject.hpp"
#include "GameObjects/PhysicalObject.hpp"
#include "Scenes/Scene.hpp"

class GameScene : public Scene {
private:
	std::vector<ptr_GameObject> gameObjects_;
	std::vector<ptr_PhysicalObject> physicalObjects_;
	std::vector<Layer> getLayers();
	void removeToBeDestroyed();
	double gameSpeed=0;

public:

	void onStart() override;
	void onLoop() override;
	void onGraphics() override;
	void onEndLoop() override;

	void addGameObject(ptr_GameObject gameObject);
	void addGameObject(ptr_PhysicalObject physicalObject);
};