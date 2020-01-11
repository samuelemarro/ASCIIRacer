#pragma once
#include "Scenes/Scene.hpp"

class MenuScene : public Scene {
	protected:
	public:
		void onStart() override;
		void onLoop() override;
		void onGraphics() override;
		void onEndLoop() override;
};