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

void MenuScene::addOption(string name, string s) {
	this->options.push_back(pss(name, s));
}

void MenuScene::fetchOptions() {
	addOption("PLAY", "GameScene");
	addOption("OPTIONS", " ");
	addOption("CREDITS", " ");
	//EXIT opzione deve essere ultima aggiunta
	addOption("EXIT", " ");
}

void MenuScene::drawMenu() {
	Graphics::write(marginX, marginY, "ASCIIRacer");
	for (int i = 0; i < this->options.size(); i++) {
		Graphics::write((float)marginX, (float)marginY + (i + 1) * (float)distanceY, this->options[i].first);
	}
}

void MenuScene::moveCursor(bool down) {
	if (down && (this->cursor< this->options.size()-1)) this->cursor++;
	else if(!down && this->cursor>0) this->cursor--;
}

void MenuScene::onStart(){
	fetchOptions();
}

void MenuScene::onLoop() {
	if (this->status.isPressed(Key::Down)) moveCursor(true);
	else if (this->status.isPressed(Key::Up)) moveCursor(false);

	this->status = Keyboard::currentStatus;
	bool change = false;
	if (this->status.isPressed(Key::Confirm)) change = true;
	if (this->options[this->cursor].second != " " && change) GameEngine::changeScene(this->options[this->cursor].second);
	else if (this->cursor == this->options.size() - 1 && change) exit(EXIT_SUCCESS);
}

void MenuScene::onGraphics() {
	drawMenu();
	Graphics::write((float)marginX - 1, (float)marginY + (this->cursor + 1) * (float)distanceY, " ");
	Graphics::write((float)marginX - 1, (float)marginY + (this->cursor + 1) * (float)distanceY, ">");
}

void MenuScene::onEndLoop() {

}