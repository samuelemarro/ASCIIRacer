#include "GameObjects/LevelObjects/Obstacle.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Obstacle::Obstacle(Point2D position, int d) {
	this->name = "Obstacle";
	this->damage = d;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Obstacle.txt", size, this->collisionMask);
	this->rect = Rect(position, size);
}

void Obstacle::onStart() {}
void Obstacle::onUpdate() {}
void Obstacle::onCollision(ptr_GameObject collider) {
	this->toBeDestroyed = true;
}
