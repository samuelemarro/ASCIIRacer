#include "GameObjects/LevelObjects/RoadLine.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"
#include "Engine/GameEngine.hpp"

RoadLine::RoadLine(Point2D position) {
	this->layer = Layer::Background_1;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/RoadLine.txt", size);
	this->rect = Rect(position, size);
}

void RoadLine::onStart() {}
void RoadLine::onUpdate() {}