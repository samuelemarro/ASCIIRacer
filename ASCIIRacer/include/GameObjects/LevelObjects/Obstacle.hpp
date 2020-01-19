#pragma once

#include "GameObjects/GameObject.hpp"

class Obstacle : public GameObject {
public:

	void onStart() override;
	void onUpdate() override;

	Obstacle(Point2D position, int d);
};