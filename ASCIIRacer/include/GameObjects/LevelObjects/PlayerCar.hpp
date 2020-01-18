#pragma once

#include "GameObjects/GameObject.hpp"

class PlayerCar : public GameObject
{
public:
	int level = 0;
	int points = 0;
	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_GameObject collider, bool horizontal);

	PlayerCar(Point2D position);
};