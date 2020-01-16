#pragma once

#include "GameObjects/GameObject.hpp"

class Obstacle : public GameObject {
public:
	int damage;

	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_GameObject collider) override;

	Obstacle(Point2D position, int d);
};