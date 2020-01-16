#include "Engine/GameEngine.hpp"
#include "Engine/Graphics.hpp"
#include "GameObjects/GameObject.hpp"
#include "Core/Rect.hpp"
#include "Core/Utilities.hpp"

GameObject::GameObject() {
	this->collisionMask = vector<vector<bool>>();
	this->immovable = false;
	this->initialised = false;
	this->layer = Layer::Content;
	this->rect = Rect(Point2D(0, 0), Graphics::errorSize);
	this->sprite = Graphics::errorSprite;
	this->toBeDestroyed = false;
	this->velocity = Point2D(0, 0);
	this->checkCollisions = true;
}

void GameObject::destroy() {
	this->toBeDestroyed = true;
}

void GameObject::onStart() {}
void GameObject::onUpdate() {}

void GameObject::onCollision(GameObject* collider)
{
}
