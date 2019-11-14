#include "Engine/GameEngine.hpp"
#include "GameObjects/GameObject.hpp"
#include "Core/Rect.hpp"
#include "Core/Utilities.hpp"

GameObject::GameObject() : layer(Layer::Content) {
}

GameObject::GameObject(Rect rect, Layer layer) : GameObject() {
	this->rect = rect;
	this->layer = layer;
}

GameObject::GameObject(Rect rect, Layer layer, Sprite sprite) : GameObject(rect, layer) {
	this->sprite = sprite;
}

void GameObject::destroy() {
	this->toBeDestroyed = true;
}

void GameObject::onStart() {}
void GameObject::onUpdate() {}