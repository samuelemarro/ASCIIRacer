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

void inputTest(bool redraw) {
	PlayerCar car = PlayerCar(Point2D(5, 5));

	int fps = 20;
	float deltaTime = 1 / (float)fps;
	float speed = 30;
	float attrition = 1;

	while (true)
	{
		sleep_for(milliseconds(1000 / fps));
		Keyboard::updateStatus();
		KeyboardStatus status = Keyboard::currentStatus;
		if (status.isDown(Key::Right))
		{
			car.rect.position.x += speed * deltaTime;
		}
		else if (status.isDown(Key::Left)) {
			car.rect.position.x -= speed * deltaTime;
		}
		else if (status.isDown(Key::Up)) {
			car.rect.position.y -= speed * deltaTime;
		}
		else if (status.isDown(Key::Down)) {
			car.rect.position.y += speed * deltaTime;
		}

		Graphics::clearBuffer();

		Graphics::draw(&car);
		if (redraw) {
			Graphics::redrawScreen();
		}
		else {
			Graphics::updateScreen();
		}
	}
}

void sceneTest() {
	PlayerCar car = PlayerCar(Point2D(5, 5));
	MenuScene menuScene;
	GameEngine::start(&menuScene);
	int fps = 60;
	GameEngine::fps = fps;
	while (true)
	{
		//sleep_for(milliseconds(1000 / fps));
		GameEngine::loop();

	}
}

void colorTest() {
	HANDLE hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (k = 1; k < 5000; k++)
	{
		SetConsoleTextAttribute(hConsole, k);
		cout << k << " Test colori!" << endl;
	}

	cin.get();
}

int main()
{
	System::initialise();
	Graphics::initialise();

	//colorTest();
	sceneTest();

	return 0;
}