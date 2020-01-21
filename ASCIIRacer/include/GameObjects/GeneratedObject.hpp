#pragma once

#include "Levels/Level.hpp"
#include "GameObjects/GameObject.hpp"

class GeneratedObject : public GameObject {
public:
	ptr_Level parentLevel;
	int generationId;

	void onStart() override;
	void onUpdate() override;

	GeneratedObject();
	GeneratedObject(ptr_Level parentLevel, int generationId);
};

typedef GeneratedObject* ptr_GeneratedObject;