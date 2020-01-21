#include "Scenes/GameOverScene.hpp"
#include "Scenes/MenuScene.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/System.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/GameScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Graphics.hpp"

#include "windows.h"
#include <utility>
#include <cstdlib>
#include <iostream>

using namespace std;
typedef pair<string, string> pss;

const int marginY = 2;
const int marginX = 30;
const int distanceY = 2;

void GameOverScene::addOption(string name, string s) {
	this->options.push_back(pss(name, s));
}

void GameOverScene::fetchOptions() {
	addOption("NEW GAME", "GameScene");
	addOption("MAIN MENU", "MenuScene");
}

void GameOverScene::drawMenu() {
	Graphics::write(marginX, marginY, "GAME OVER");
	for (int i = 0; i < this->options.size(); i++) {
		Graphics::write((float)marginX, (float)marginY + (i + 1) * (float)distanceY, this->options[i].first);
	}
}

void GameOverScene::moveCursor(bool down) {
	if (down && (this->cursor < this->options.size() - 1)) this->cursor++;
	else if (!down && this->cursor > 0) this->cursor--;
}

void GameOverScene::onStart() {
	fetchOptions();
}

void GameOverScene::onLoop() {
	if (this->status.isPressed(Key::Down)) moveCursor(true);
	else if (this->status.isPressed(Key::Up)) moveCursor(false);

	this->status = Keyboard::currentStatus;
	bool change = false;
	if (this->status.isPressed(Key::Confirm)) change = true;
	if (this->options[this->cursor].second != " " && change) GameEngine::changeScene(this->options[this->cursor].second);
}

void GameOverScene::onGraphics() {
	drawMenu();
	Graphics::write((float)marginX - 1, (float)marginY + (this->cursor + 1) * (float)distanceY, " ");
	Graphics::write((float)marginX - 1, (float)marginY + (this->cursor + 1) * (float)distanceY, ">");
}

void GameOverScene::onEndLoop() {

}