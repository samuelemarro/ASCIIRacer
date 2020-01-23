#pragma once
#include "GameObjects/GameObject.hpp"

class Popup : public GameObject {
private:
	float shownTime;
public:
	bool active;
	float currentDuration;

	void onStart();
	void onUpdate();

	void notify(std::string spritePath, float duration);

	Popup(Point2D position);
};

typedef Popup* ptr_Popup;