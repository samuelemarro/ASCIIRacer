#include "GameObjects/LevelObjects/Border.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Border::Border(Point2D position, int rw) {
	this->roadWidth = rw;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 3);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Border.txt", size, &this->collisionMask);
	this->rect = Rect(position, size);
}

void Border::onStart() {}
void Border::onUpdate() {}
void Border::onCollision(ptr_PhysicalObject collider) {}