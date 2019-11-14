#pragma once

#include <vector>
#include <chrono>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/PhysicalObject.hpp"
#include "Scenes/Scene.hpp"


class GameEngine
{
private:
	GameEngine();
	static std::chrono::time_point<std::chrono::steady_clock> lastLoopTime_;

public:
	static ptr_Scene currentScene;

	static int fps;

	static void start(ptr_Scene firstScene);

	static void loop();

	static float deltaTime();
};