#pragma once

#include "GameObjects/GameObject.hpp"

class AICar : public GameObject
{
public:
	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_GameObject collider) override;

	AICar(Point2D position);
};