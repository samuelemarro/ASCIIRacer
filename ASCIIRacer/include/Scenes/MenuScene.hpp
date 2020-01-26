#pragma once
#include "Scenes/Scene.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Core/Typedefs.hpp"
#include "Core/Rect.hpp"
#include "windows.h"
#include <utility>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class MenuScene : public Scene {
private:
	KeyboardStatus status;
	vector<pair<string, string>> options;
	Sprite titleSprite;
	Rect titleRect;

	int cursor = 0;
	void fetchOptions();
	void drawMenu(int xOffset, int yOffset);
	void moveCursor(bool down);
	void addOption(string name, string s);
public:
	void onStart() override;
	void onLoop() override;
	void onGraphics() override;
	void onEndLoop() override;
};