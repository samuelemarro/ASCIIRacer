#include "GameObjects/LevelObjects/Obstacle.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Obstacle::Obstacle(Point2D position, int d, int t, ptr_Level parentLevel, int generationId) {
	this->name = "Obstacle";
	this->damage = d;
	this->type = t;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Obstacle" + to_string(this->type) + ".txt", size);
	this->rect = Rect(position, size);
	this->solid = false;
	this->parentLevel = parentLevel;
	this->generationId = generationId;
}

void Obstacle::onStart() {}
void Obstacle::onUpdate() {}