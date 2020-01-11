#pragma once
#include "Scenes/Scene.hpp"

class MenuScene : public Scene {
	protected:
		void fetchOptions();
		void drawMenu();
		void moveCursor(bool down);
	public:
		void onStart() override;
		void onLoop() override;
		void onGraphics() override;
		void onEndLoop() override;
};