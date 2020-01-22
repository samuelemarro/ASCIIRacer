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

void MenuScene::drawMenu(int xOffset, int yOffset) {
	//Graphics::write(xOffset, yOffset, "ASCIIRacer");
	for (int i = 0; i < this->options.size(); i++) {
		Graphics::write((float)xOffset, (float)yOffset + (i + 1) * (float)distanceY, this->options[i].first);
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

	Size size;
	Sprite s = Graphics::loadSpriteFromFile(System::getExecutableDirectory() + "/sprites/TitleScreen.txt", size);
	int titleOffset = (Graphics::screenSize.width - size.width) / 2;
	Rect r = Rect(Point2D(titleOffset, 0), size);
	Graphics::draw(r, s);

	int maxLength = -1;

	for (pss pair : this->options) {
		if ((int)pair.first.size() > maxLength) {
			maxLength = pair.first.size();
		}
	}

	int textOffsetX = (Graphics::screenSize.width - maxLength) / 2;
	int textOffsetY = r.position.y + r.size.height;
	
	drawMenu(textOffsetX, textOffsetY);
	//Graphics::write((float)marginX - 1, (float)marginY + (this->cursor + 1) * (float)distanceY, " ");
	Graphics::write((float)textOffsetX - 1, (float)textOffsetY + (this->cursor + 1) * (float)distanceY, ">");
}

void MenuScene::onEndLoop() {

}