#pragma once

#include <vector>
#include <chrono>
#include <string>
#include "Scenes/GameScene.hpp"
#include "Scenes/GameOverScene.hpp"
#include "Scenes/MenuScene.hpp"

#include "GameObjects/GameObject.hpp"
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"


class GameEngine
{
private:
	static GameScene* gameScene;
	static GameOverScene* gameOverScene;
	static MenuScene* menuScene;

	GameEngine();
	static std::chrono::time_point<std::chrono::steady_clock> lastLoopTime_;

	static ptr_Scene nextScene;

public:
	static ptr_Scene currentScene;

	static int fps;

	static void start(ptr_Scene firstScene);
	
	static void changeScene(std::string name);

	static void loop();

	static float deltaTime();
};