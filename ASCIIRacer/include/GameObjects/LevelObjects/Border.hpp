#pragma once

#include "GameObjects/GameObject.hpp"

class Border : public GameObject {
public:
	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_GameObject collider) override;

	Border(Point2D position);
};