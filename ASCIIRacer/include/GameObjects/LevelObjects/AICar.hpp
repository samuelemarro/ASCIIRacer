#pragma once

#include "Core/CollisionInfo.hpp"
#include "GameObjects/GeneratedObject.hpp"

class AICar : public GeneratedObject
{
public:
	void onStart() override;
	void onUpdate() override;

	void onCollision(CollisionInfo collisionInfo);

	AICar(Point2D position);
};