#pragma once

#include "GameObjects/GameObject.hpp"

class Upgrade : public GameObject {
public:

	void onStart() override;
	void onUpdate() override;

	Upgrade(Point2D position, int b);
};