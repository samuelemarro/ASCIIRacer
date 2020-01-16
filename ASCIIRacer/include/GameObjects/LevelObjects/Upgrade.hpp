#pragma once

#include "GameObjects/GameObject.hpp"

class Upgrade : public GameObject {
public:
	int bonus;

	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_GameObject collider) override;

	Upgrade(Point2D position, int b);
};