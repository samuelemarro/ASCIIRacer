#include "GameObjects/LevelObjects/Upgrade.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Upgrade::Upgrade(Point2D position, int b, ptr_Level parentLevel, int generationId) {
	this->name = "Upgrade";
	this->bonus = b;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 3);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Upgrade.txt", size);
	this->rect = Rect(position, size);
	this->solid = false;
	this->parentLevel = parentLevel;
	this->generationId = generationId;
}

void Upgrade::onStart() {}
void Upgrade::onUpdate() {}
