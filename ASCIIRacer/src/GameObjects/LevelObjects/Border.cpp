#include "GameObjects/LevelObjects/Border.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

Border::Border(Point2D position) {
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 3);
	this->immovable = true;
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/Border.txt", size);
	this->rect = Rect(position, size);
}

void Border::onStart() {}
void Border::onUpdate() {}
void Border::onCollision(ptr_GameObject collider) {}