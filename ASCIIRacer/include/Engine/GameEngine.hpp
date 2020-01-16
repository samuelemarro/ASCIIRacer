#pragma once

#include <vector>
#include <chrono>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"


class GameEngine
{
private:
	GameEngine();
	static std::chrono::time_point<std::chrono::steady_clock> lastLoopTime_;

	static ptr_Scene nextScene;

public:
	static ptr_Scene currentScene;

	static int fps;

	static void start(ptr_Scene firstScene);

	static void changeScene(ptr_Scene newScene);

	static void loop();

	static float deltaTime();
};