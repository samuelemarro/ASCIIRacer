#include "Engine/GameEngine.hpp"
#include "Engine/Graphics.hpp"
#include "GameObjects/GameObject.hpp"
#include "Core/Rect.hpp"
#include "Core/Utilities.hpp"

GameObject::GameObject() {
	this->initialised = false;
	this->layer = Layer::Content;
	this->rect = Rect(Point2D(0, 0), Graphics::errorSize);
	this->sprite = Graphics::errorSprite;
	this->toBeDestroyed = false;
	this->velocity = Point2D(0, 0);
	this->solid = true;
}

void GameObject::destroy() {
	this->toBeDestroyed = true;
}

Point2D GameObject::futurePosition()
{
	Point2D futurePos = this->rect.position;
	futurePos.x += this->velocity.x * GameEngine::deltaTime();
	futurePos.y += this->velocity.y * GameEngine::deltaTime();

	return futurePos;
}

void GameObject::onStart() {}
void GameObject::onUpdate() {}
