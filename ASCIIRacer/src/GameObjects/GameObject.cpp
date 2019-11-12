#include "GameObjects/GameObject.hpp"
#include "Core/Rect.hpp"
#include "Core/Utilities.hpp"

GameObject::GameObject(Rect rect, Layer layer) : rect(rect), layer(layer) {
	this->sprite = new char[rect.size.length()];
	Utilities::fill2D(this->sprite, rect.size, '?');
}

GameObject::GameObject(Rect rect, Layer layer, char* sprite) : rect(rect), layer(layer), sprite(sprite) {
}

void GameObject::onStart(){}
void GameObject::onUpdate(){}