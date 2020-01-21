#include "GameObjects/LevelObjects/Obstacle.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Obstacle::Obstacle(Point2D position, int d, ptr_Level parentLevel, int generationId) {
	this->name = "Obstacle";
	this->damage = d;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Obstacle.txt", size);
	this->rect = Rect(position, size);
	this->solid = false;
	this->parentLevel = parentLevel;
	this->generationId = generationId;
}

void Obstacle::onStart() {}
void Obstacle::onUpdate() {}