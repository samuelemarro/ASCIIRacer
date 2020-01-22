#pragma once

class CollisionType {
public:
	bool top;
	bool bottom;
	bool left;
	bool right;
	bool any;

	CollisionType();
	CollisionType(bool top, bool bottom, bool left, bool right, bool any);
};