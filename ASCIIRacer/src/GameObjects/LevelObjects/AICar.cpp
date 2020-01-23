#include "GameObjects/LevelObjects/AICar.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

AICar::AICar(Point2D position, int d) {
	this->name = "AICar";
	this->damage = d;
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 1);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/AICar.txt", size);
	this->rect = Rect(position, size);
}

void AICar::onStart() {}
void AICar::onUpdate() {
}

void AICar::onCollision(CollisionInfo collisionInfo)
{
	ptr_GameObject collider = collisionInfo.collider;
	if (collider->name == "Road") {
		if (collisionInfo.future.left || collisionInfo.future.right || collisionInfo.future.top) {
			this->velocity.x = 0;
		}

		if (collisionInfo.present.top) {
			//Scontro verticale
			//TODO: Non è garantito che questo controllo sia corretto
			if (this->rect.position.x + this->rect.size.width > 40) {
				this->rect.position.x--;
			}
			else if (this->rect.position.x <= 30) {
				this->rect.position.x++;
			}

			this->velocity.x = 0;
		}
	}
}
