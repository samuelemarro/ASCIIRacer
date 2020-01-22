#pragma once

#include "GameObjects/GameObject.hpp"
#include "Core/CollisionInfo.hpp"

class PlayerCar : public GameObject
{
public:
	int level = 0;
	int points = 0;
	void onStart() override;
	void onUpdate() override;
	void onCollision(CollisionInfo collisionInfo);

	PlayerCar(Point2D position);
};