#include "Core/CollisionType.hpp"

CollisionType::CollisionType()
{
	this->top = false;
	this->bottom = false;
	this->left = false;
	this->right = false;
	this->any = false;
}

CollisionType::CollisionType(bool top, bool bottom, bool left, bool right, bool any)
{
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right = right;
	this->any = any;
}