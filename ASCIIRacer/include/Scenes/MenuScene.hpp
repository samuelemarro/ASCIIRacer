#pragma once
#include "Scenes/Scene.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "windows.h"
#include <utility>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class MenuScene : public Scene {
	protected:
		KeyboardStatus status;
		vector<pair<string, string> > options;
		int cursor=0;
		void fetchOptions();
		void drawMenu();
		void moveCursor(bool down);
		void addOption(string name, string s);
	public:
		void onStart() override;
		void onLoop() override;
		void onGraphics() override;
		void onEndLoop() override;
};