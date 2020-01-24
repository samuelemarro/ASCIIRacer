#pragma once

#include "Core/Layer.hpp"
#include "Core/Rect.hpp"
#include "Core/Typedefs.hpp"
#include <string>

using std::string;
using std::to_string;

class GameObject {
public:
	string name;
	Rect rect;
	Layer layer;
	Sprite sprite;
	bool initialised;
	bool toBeDestroyed;

	bool solid;
	Point2D velocity;

	virtual void onStart();
	virtual void onUpdate();

	void destroy();

	Point2D futurePosition();

	GameObject();
};

typedef GameObject* ptr_GameObject;