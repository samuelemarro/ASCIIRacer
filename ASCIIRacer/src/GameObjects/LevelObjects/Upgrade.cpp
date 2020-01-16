#include "GameObjects/LevelObjects/Upgrade.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Upgrade::Upgrade(Point2D position, int b) {
	this->bonus = b;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Upgrade.txt", size, &this->collisionMask);
	this->rect = Rect(position, size);
}

void Upgrade::onStart() {}
void Upgrade::onUpdate() {}
void Upgrade::onCollision(ptr_PhysicalObject collider) {}