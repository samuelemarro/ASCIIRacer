#pragma once
#include "Scenes/Scene.hpp"
#include "windows.h"
#include <utility>
#include <cstdlib>
#include <iostream>

using namespace std;

class MenuScene : public Scene {
	protected:
		void fetchOptions();
		void drawMenu();
		void moveCursor(bool down);
		void addOption(string name, ptr_Scene s);
	public:
		void onStart() override;
		void onLoop() override;
		void onGraphics() override;
		void onEndLoop() override;
};