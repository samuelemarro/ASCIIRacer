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
	vector<pair<string, ptr_Scene> > options;
	int cursor=0;
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