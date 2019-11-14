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
	bool initialised = false;
	bool toBeDestroyed = false;

	virtual void onStart();
	virtual void onUpdate();

	void destroy();

	GameObject(Rect rect, Layer layer);
	GameObject(Rect rect, Layer layer, Sprite sprite);
	GameObject();
};

typedef GameObject* ptr_GameObject;