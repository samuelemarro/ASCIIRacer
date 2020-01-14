#pragma once

#include "Core/Layer.hpp"
#include "Core/Rect.hpp"
#include "Core/Typedefs.hpp"
#include <string>

class GameObject
{
private:
public:
	Rect rect;
	Layer layer;
	Sprite sprite;
	double gameSpeed = 1;
	bool initialised = false;
	bool toBeDestroyed = false;

	virtual void onStart();
	virtual void onUpdate();

	void destroy();

	Point2D velocity;

	GameObject(Rect rect, Layer layer);
	GameObject(Rect rect, Layer layer, Sprite sprite);
	GameObject();
};

typedef GameObject* ptr_GameObject;