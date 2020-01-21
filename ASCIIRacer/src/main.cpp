#include <iostream>
#include "stdlib.h"

#include "Core/Layer.hpp"
#include "Engine/Key.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "Engine/GameEngine.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/MenuScene.hpp"

#include "windows.h"

using namespace std;

#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

void sceneTest() {
	PlayerCar car = PlayerCar(Point2D(5, 5));
	MenuScene menuScene;
	int fps = 60;
	GameEngine::fps = fps;
	GameEngine::start(&menuScene);
	while (true)
	{
		//sleep_for(milliseconds(1000 / fps));
		GameEngine::loop();

	}
}

int main()
{
	System::initialise();
	Graphics::initialise();
	sceneTest();

	return 0;
}