#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

PlayerCar::PlayerCar(Point2D position) {
	//this->sprite = Graphics::loadSpriteFromFile
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 0);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/PlayerCar.txt", size);
	this->rect = Rect(position, size);
}

void PlayerCar::onStart() {}
void PlayerCar::onUpdate() {
	float speedX = 100;
	float speedY = 50;
	KeyboardStatus status = Keyboard::currentStatus;
	/*if (status.isPressed(Key::Right) && rect.position.x < 21)
	{
		rect.position.x += 7;
	}
	else if (status.isPressed(Key::Left) && rect.position.x>0) {
		rect.position.x -= 7;
	}
	else {
		velocity.x = 0;
	}*/
	
	if (status.isDown(Key::Right)) {
		velocity.x = speedX;
	}
	else if (status.isDown(Key::Left)) {
		velocity.x = -speedX;
	}
	else {
		velocity.x = 0;
	}

	if (status.isDown(Key::Up)) {
		velocity.y = -speedY;
	}
	else if (status.isDown(Key::Down)) {
		velocity.y = speedY;
	}
	else {
		velocity.y = 0;
	}
	
}
void PlayerCar::onCollision(ptr_GameObject collider) {}