#include "GameObjects/LevelObjects/WeirdWall.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

WeirdWall::WeirdWall(Point2D position, float speed) {
	this->layer = Layer::Content;
	this->immovable = true;
	this->speed = speed;
	this->velocity = Point2D(speed, 0);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/WeirdWall.txt", size, &this->collisionMask);
	this->rect = Rect(position, size);
}

void WeirdWall::onStart()
{
}

void WeirdWall::onUpdate()
{
	if (this->rect.position.x > 20) {
		this->velocity.x = -this->speed;
	}
	else if (this->rect.position.x < 5) {
		this->velocity.x = this->speed;
	}
	else if (this->velocity.x == 0) {
		this->velocity.x = this->speed;
	}

}

void WeirdWall::onCollision(PhysicalObject* collider)
{
	this->sprite[2][2] += 1;
}
