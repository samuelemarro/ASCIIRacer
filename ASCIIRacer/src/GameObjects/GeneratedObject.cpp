#include "GameObjects/GeneratedObject.hpp"

void GeneratedObject::onUpdate()
{
}

GeneratedObject::GeneratedObject()
{
	this->parentLevel = NULL;
	this->generationId = -1;
}

GeneratedObject::GeneratedObject(ptr_Level parentLevel, int generationId)
{
	this->parentLevel = parentLevel;
	this->generationId = generationId;
}
