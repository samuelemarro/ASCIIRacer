#pragma once

#include "GameObjects/GameObject.hpp"

class Border : public GameObject {
public:
	void onStart() override;
	void onUpdate() override;

	Border(Point2D position);
};