#pragma once

class Scene {
public:
	bool initialised = false;

	virtual void onStart() = 0;

	virtual void onLoop() = 0;
	virtual void onGraphics() = 0;
	virtual void onEndLoop() = 0;
};

typedef Scene* ptr_Scene;