#pragma once

#include "Core/Layer.hpp"
#include "Core/Rect.hpp"
#include "Core/Typedefs.hpp"
#include <string>

class GameObject
{
private:
	void loadSprite(std::string path);

public:
	Rect rect;
	Layer layer;
	Sprite sprite;
	//Considerare bool started;

	virtual void onStart();
	virtual void onUpdate();

	GameObject(Rect rect, Layer layer);
	GameObject(Rect rect, Layer layer, Sprite sprite);
	GameObject();
};