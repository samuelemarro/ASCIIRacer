#pragma once
#include "Scenes/Scene.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "windows.h"
#include <utility>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

class GameOverScene : public Scene {
protected:
	KeyboardStatus status;
	vector<pair<string, string> > options;
	int cursor=0;
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