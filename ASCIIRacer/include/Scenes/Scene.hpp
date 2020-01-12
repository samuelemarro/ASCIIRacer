#pragma once
#include <iostream>

class Scene {
public:
	bool initialised = false;
	Scene* nextScene = NULL;

	virtual void onStart() = 0;

	virtual void onLoop() = 0;
	virtual void onGraphics() = 0;
	virtual void onEndLoop() = 0;
};

typedef Scene* ptr_Scene;