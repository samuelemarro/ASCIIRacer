#include "GameObjects/Popup.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/System.hpp"
#include "Engine/Graphics.hpp"

Popup::Popup(Point2D position) {
	this->rect = Rect(position, Size(0, 0));
	this->sprite = Sprite();
}

void Popup::onStart()
{
}

void Popup::onUpdate() {
	if (active) {
		shownTime += GameEngine::deltaTime();
		
		if (shownTime > currentDuration) {
			this->rect.size = Size(0, 0);
			active = false;
		}
	}
}

void Popup::notify(std::string spritePath, float duration) {
	this->sprite = Graphics::loadSpriteFromFile(spritePath, this->rect.size);
	active = true;
	shownTime = 0;
	currentDuration = duration;
}