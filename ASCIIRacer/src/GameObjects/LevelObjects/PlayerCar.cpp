#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"

//Sprite playerCarSprite = { "/-\\|O|\\-/"};

Layer playerCarLayer = Layer::Content;

PlayerCar::PlayerCar(Point2D position) : Car() {
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
void PlayerCar::onUpdate() {}
void PlayerCar::onCollision(PhysicalObject collider) {}