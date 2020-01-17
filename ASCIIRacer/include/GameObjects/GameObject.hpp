#pragma once

#include "Core/Layer.hpp"
#include "Core/Rect.hpp"
#include "Core/Typedefs.hpp"
#include <string>

using std::string;

class GameObject
{
public:
	string name;
	Rect rect;
	Layer layer;
	Sprite sprite;
	bool initialised;
	bool toBeDestroyed;
	double gameSpeed;

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