#include "GameObjects/LevelObjects/RoadLine.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"
#include "Levels/Level.hpp"

#include "Engine/System.hpp"
#include "Engine/GameEngine.hpp"

RoadLine::RoadLine(Point2D position, char c) {
	this->layer = Layer::Background_1;
	this->velocity = Point2D(0, 0.05);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->immovable = true;
	if(c=='n') this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/RoadLine.txt", size);
	else if(c=='d') this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/RoadLineRight.txt", size);
	else if(c=='s') this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/RoadLineLeft.txt", size);
	this->rect = Rect(position, size);
}

void RoadLine::onStart() {}
void RoadLine::onUpdate() {
	this->rect.position.y += this->velocity.y;
}