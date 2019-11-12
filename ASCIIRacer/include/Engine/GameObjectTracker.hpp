#pragma once

#include "GameObjects/GameObject.hpp"

class GameObjectTracker {
public:
	GameObject gameObject;
	bool handlePhysics;
	bool handleKeyboard;
	bool toBeAdded;
	bool toBeDestroyed;
};