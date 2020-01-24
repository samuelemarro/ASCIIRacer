#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/LevelObjects/Upgrade.hpp"
#include "GameObjects/LevelObjects/Obstacle.hpp"
#include "GameObjects/LevelObjects/AICar.hpp"
#include "Engine/Graphics.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

PlayerCar::PlayerCar(Point2D position, float maxSpeed) {
	this->name = "PlayerCar";
	this->layer = Layer::Content;
	this->maxSpeed = maxSpeed;
	this->velocity = Point2D(0, 0);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/PlayerCar.txt", size);
	this->rect = Rect(position, size);
}

void PlayerCar::onStart() {}
void PlayerCar::onUpdate() {
	float speedX = 100;
	float speedY = 50;
	KeyboardStatus status = Keyboard::currentStatus;
	if (status.isDown(Key::Right)) {
		velocity.x = maxSpeed;// max(0, min(maxSpeed, velocity.x + accelleration * GameEngine::deltaTime()));
	}
	else if (status.isDown(Key::Left)) {
		velocity.x = -maxSpeed; // min(0, max(-maxSpeed, velocity.x - accelleration * GameEngine::deltaTime()));
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
			else{ 
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

	//cast per poter accedere ai rispettivi campi
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
		GameScene* scene = (GameScene*)GameEngine::currentScene;
		this->points -= 15 * scene->currentLevel->difficulty;
	}
	else if (collider->name == "AICar") {
		AICar* aicar = dynamic_cast<AICar*>(collider);
		this->points -= aicar->damage;
	}
}