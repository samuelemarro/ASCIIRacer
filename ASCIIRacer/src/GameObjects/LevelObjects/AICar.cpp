#include "GameObjects/LevelObjects/AICar.hpp"
#include "Engine/Graphics.hpp"


AICar::AICar(Point2D position, int damage) {
	this->name = "AICar";
	this->damage = damage;
	this->layer = Layer::Foreground_2;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/AICar.txt", size);
	this->rect = Rect(position, size);
}

void AICar::onUpdate() {
}

void AICar::onCollision(CollisionInfo collisionInfo)
{
	ptr_GameObject collider = collisionInfo.collider;
	if (collider->name == "Road") {
		if (collisionInfo.future.any && collisionInfo.present.any) {
			//Scontro verticale
			if (collisionInfo.future.left) {
				this->rect.position.x++;
			}
			else {
				this->rect.position.x--;
			}
		}
	}
	else if (collider->name == "AICar"){
		this->velocity.x = 0;
		collider->velocity.x = 0;

		if (collisionInfo.future.any && collisionInfo.present.any) {
			if (collisionInfo.future.left) {
				this->rect.position.x++;
			}
			else {
				this->rect.position.x--;
			}
		}
	}
}