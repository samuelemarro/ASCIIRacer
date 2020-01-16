#pragma once

#include "Core/Layer.hpp"
#include "Core/Rect.hpp"
#include "Core/Typedefs.hpp"
#include <string>

class GameObject
{
public:
	Rect rect;
	Layer layer;
	Sprite sprite;
	bool initialised;
	bool toBeDestroyed;

	bool checkCollisions;
	CollisionMask collisionMask;
	Point2D velocity;
	bool immovable;

	virtual void onStart();
	virtual void onUpdate();
	virtual void onCollision(GameObject* collider);

	void destroy();

	GameObject();
};

typedef GameObject* ptr_GameObject;