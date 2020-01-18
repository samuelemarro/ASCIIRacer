#pragma once
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"
#include "Levels/Level.hpp"

class GameScene : public Scene {
private:
	std::vector<ptr_GameObject> gameObjects_;
	std::vector<Layer> getLayers();
	
	void removeToBeDestroyed();
	double gameSpeed = 0;    //probabilmente da togliere, l'attributo della velocità del gioco ce l'ha il livello

	std::vector<std::vector<std::vector<int>>> collisionBuffer;

	void checkCollisions();
public:

	ptr_Level currentLevel;

	void onStart() override;
	void onLoop() override;
	void onGraphics() override;
	void onEndLoop() override;

	void addGameObject(ptr_GameObject gameObject);
};