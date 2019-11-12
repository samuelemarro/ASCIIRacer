#include <iostream>
#include "stdlib.h"

#include "Core/Layer.hpp"
#include "Engine/Key.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"

using namespace std;

#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

void inputTest(bool redraw) {
	PlayerCar car = PlayerCar(Point2D(5, 5));

	int fps = 20;
	float deltaTime = 1 / (float)fps;
	float speed = 30;
	float attrition = 1;

	while (true)
	{
		sleep_for(milliseconds(1000 / fps));
		KeyboardStatus* status = Keyboard::getStatus();
		if (status->isDown(Key::Right))
		{
			car.rect.position.x += speed * deltaTime;
		}
		else if (status->isDown(Key::Left)) {
			car.rect.position.x -= speed * deltaTime;
		}
		else if (status->isDown(Key::Up)) {
			car.rect.position.y -= speed * deltaTime;
		}
		else if (status->isDown(Key::Down)) {
			car.rect.position.y += speed * deltaTime;
		}

		Graphics::clearBuffer();
		Graphics::draw(car);
		if (redraw) {
			Graphics::redrawScreen();
		}
		else {
			Graphics::updateScreen();
		}
		//cout << car.rect.position.x << endl;
		delete status;
	}
}

int main()
{
	System::initialise();
	Graphics::initialise();

	inputTest(false);

	return 0;
}