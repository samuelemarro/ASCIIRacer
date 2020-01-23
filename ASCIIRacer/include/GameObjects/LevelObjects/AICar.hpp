#pragma once

#include "Core/CollisionInfo.hpp"
#include "GameObjects/GeneratedObject.hpp"

class AICar : public GeneratedObject {
public:
	int damage;

	void onStart() override;
	void onUpdate() override;

	void onCollision(CollisionInfo collisionInfo);

	AICar(Point2D position, int d);
};