#include "GameObjects/LevelObjects/Upgrade.hpp"

#include "Engine/Graphics.hpp"

Upgrade::Upgrade(Point2D position, int bonus, int type, ptr_Level parentLevel, int generationId) {
	this->name = "Upgrade";
	this->bonus = bonus;
	this->type = type;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 3);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Upgrade" + to_string(this->type) + ".txt", size);
	this->rect = Rect(position, size);
	this->solid = false;
	this->parentLevel = parentLevel;
	this->generationId = generationId;
}