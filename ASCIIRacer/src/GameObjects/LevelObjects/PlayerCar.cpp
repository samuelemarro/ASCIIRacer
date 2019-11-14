#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

PlayerCar::PlayerCar(Point2D position) {
	//this->sprite = Graphics::loadSpriteFromFile
	this->collisionLayer = Layer::Content;
	this->layer = Layer::Content;
	this->speed = Point2D(0, 0);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile("sprites/PlayerCar.txt", size);
	this->rect = Rect(position, size);
}

void PlayerCar::onStart() {}
void PlayerCar::onUpdate() {
	float deltaTime = GameEngine::deltaTime();
	float speed = 100;
	KeyboardStatus status = Keyboard::currentStatus;
	if (status.isDown(Key::Right))
	{
		rect.position.x += speed * deltaTime;
	}
	else if (status.isDown(Key::Left)) {
		rect.position.x -= speed * deltaTime;
	}
	else if (status.isDown(Key::Up)) {
		rect.position.y -= speed * deltaTime;
	}
	else if (status.isDown(Key::Down)) {
		rect.position.y += speed * deltaTime;
	}
}
void PlayerCar::onCollision(PhysicalObject collider) {}