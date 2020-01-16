#pragma once
#include "GameObjects/GameObject.hpp"

class WeirdWall : public GameObject {
public:
	WeirdWall(Point2D position, float speed);

	float speed;

	void onStart() override;
	void onUpdate() override;
	void onCollision(GameObject* collider);
};