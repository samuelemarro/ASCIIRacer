#include "GameObjects/LevelObjects/AICar.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

AICar::AICar(Point2D position) {
	//this->sprite = Graphics::loadSpriteFromFile
	this->collisionLayer = Layer::Content;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 10);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/AICar.txt", size, &this->collisionMask);
	this->rect = Rect(position, size);
}

void AICar::onStart() {}
void AICar::onUpdate() {
}
void AICar::onCollision(ptr_PhysicalObject collider) {}