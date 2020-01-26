#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/LevelObjects/Upgrade.hpp"
#include "GameObjects/LevelObjects/Obstacle.hpp"
#include "GameObjects/LevelObjects/AICar.hpp"
#include "Engine/Graphics.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

PlayerCar::PlayerCar(Point2D position, float baseSpeed, float maxSpeed, float acceleration) {
	this->name = "PlayerCar";
	this->layer = Layer::Content;
	this->baseSpeed = baseSpeed;
	this->maxSpeed = maxSpeed;
	this->acceleration = acceleration;
	this->velocity = Point2D(0, 0);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/PlayerCar.txt", size);
	this->rect = Rect(position, size);
}

void PlayerCar::onUpdate() {
	KeyboardStatus status = Keyboard::currentStatus;
	if (status.isDown(Key::Right)) {
		if (velocity.x < baseSpeed) {
			velocity.x = baseSpeed;
		}

		velocity.x += acceleration * GameEngine::deltaTime();

		if (velocity.x > maxSpeed) {
			velocity.x = maxSpeed;
		}
	}
	else if (status.isDown(Key::Left)) {
		if (velocity.x > -baseSpeed) {
			velocity.x = -baseSpeed;
		}

		velocity.x -= acceleration * GameEngine::deltaTime();

		if (velocity.x < -maxSpeed) {
			velocity.x = maxSpeed;
		}
	}
	else {
		velocity.x = 0;
	}
}

void PlayerCar::onCollision(CollisionInfo collisionInfo) {
	ptr_GameObject collider = collisionInfo.collider;
	if (collisionInfo.future.any) {
		this->velocity.x = 0;
	}
	if (collider->name == "Road") {
		if (collisionInfo.future.any && collisionInfo.present.any) {
			//Scontro verticale
			if (collisionInfo.present.left) {
				this->rect.position.x++;
			}
			else {
				this->rect.position.x--;
			}
		}
	}
	else if (collider->name == "AICar") {
		if (collisionInfo.future.any && collisionInfo.present.any) {
			//Collisione verticale
			if (collisionInfo.future.left) {
				this->rect.position.x++;
				((AICar*)collisionInfo.collider)->rect.position.x--;
			}
			else {
				this->rect.position.x--;
				((AICar*)collisionInfo.collider)->rect.position.x++;
			}
		}
	}

	if (collider->name == "Upgrade") {
		Upgrade* up = dynamic_cast<Upgrade*>(collider);
		this->points += up->bonus;
		collider->toBeDestroyed = true;

		up->parentLevel->removedIds.push_back(up->generationId);
	}
	else if (collider->name == "Obstacle") {
		Obstacle* obs = dynamic_cast<Obstacle*>(collider);
		this->points -= obs->damage;
		collider->toBeDestroyed = true;

		obs->parentLevel->removedIds.push_back(obs->generationId);
	}
	else if (collider->name == "Road") {
		if (collisionInfo.future.left && collisionInfo.future.right)
			this->points -= 250;
		else
			this->points -= 1000 * GameEngine::deltaTime();
	}
	else if (collider->name == "AICar") {
		AICar* aicar = dynamic_cast<AICar*>(collider);
		if (collisionInfo.future.left && collisionInfo.future.right)
			this->points -= aicar->damage;
		else
			this->points -= aicar->damage * GameEngine::deltaTime();
	}
}