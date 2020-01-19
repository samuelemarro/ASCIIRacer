#include "GameObjects/LevelObjects/Obstacle.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Obstacle::Obstacle(Point2D position, int d) {
	this->name = "Obstacle";
	this->value = d;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Obstacle.txt", size);
	this->rect = Rect(position, size);
	this->solid = false;
}

void Obstacle::onStart() {}
void Obstacle::onUpdate() {}