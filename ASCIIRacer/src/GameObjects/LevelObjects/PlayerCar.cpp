#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

PlayerCar::PlayerCar(Point2D position) {
	this->name = "PlayerCar";
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 0);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/PlayerCar.txt", size, this->collisionMask);
	this->rect = Rect(position, size);
}

void PlayerCar::onStart() {}
void PlayerCar::onUpdate() {
	float speedX = 100;
	float speedY = 50;
	KeyboardStatus status = Keyboard::currentStatus;
	if (status.isDown(Key::Right)) {
		velocity.x = speedX;
	}
	else if (status.isDown(Key::Left)) {
		velocity.x = -speedX;
	}
	else {
		velocity.x = 0;
	}

	if (status.isDown(Key::Up) && this->rect.position.y>1) {
		velocity.y = -speedY;
	}
	else if (status.isDown(Key::Down) && this->rect.position.y < 27) {
		velocity.y = speedY;
	}
	else {
		velocity.y = 0;
	}
	
}
void PlayerCar::onCollision(ptr_GameObject collider) {
	if (collider->name == "Upgrade") this->points += 100;
	else if (collider->name == "Obstacle") this->points -= 100;
}