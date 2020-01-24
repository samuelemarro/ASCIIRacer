#pragma once

#include "GameObjects/GeneratedObject.hpp"

class Upgrade : public GeneratedObject {
public:
	int bonus;
	int type;

	void onStart() override;
	void onUpdate() override;

	Upgrade(Point2D position, int b, int t, ptr_Level parentLevel, int generationId);
};