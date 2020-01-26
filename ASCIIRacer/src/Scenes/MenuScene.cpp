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
	if (down && (this->cursor < this->options.size() - 1)) {
		this->cursor++;
	}
	else if (!down && this->cursor > 0) {
		this->cursor--;
	}
}

void MenuScene::onStart() {
	fetchOptions();
	Size size;
	this->titleSprite = Graphics::loadSpriteFromFile(System::getExecutableDirectory() + "/sprites/TitleScreen.txt", size);

	int titleOffset = (Graphics::screenSize.width - size.width) / 2;
	Rect rect = Rect(Point2D(titleOffset, 1), size);

	this->titleRect = rect;
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
	Graphics::draw(this->titleRect, this->titleSprite);

	//Menu
	int maxLength = -1;

	for (pss pair : this->options) {
		if ((int)pair.first.size() > maxLength) {
			maxLength = pair.first.size();
		}
	}

	int textOffsetX = (Graphics::screenSize.width - maxLength) / 2;
	float textOffsetY = this->titleRect.position.y + this->titleRect.size.height;

	drawMenu(textOffsetX, textOffsetY);
	Graphics::write((float)textOffsetX - 1, (float)textOffsetY + (this->cursor + 1) * (float)distanceY, ">");

	//Crediti
	float creditsY = Graphics::screenSize.height - 2;

	string name1 = "Samuele Marro";
	string name2 = "Edoardo Merli";
	string name3 = "Filip Radovic";

	int nameOffset1 = (Graphics::screenSize.width / 4) - (name1.size() / 2);
	Graphics::write(nameOffset1, creditsY, name1);

	int nameOffset2 = (Graphics::screenSize.width / 2) - (name2.size() / 2);
	Graphics::write(nameOffset2, creditsY, name2);

	int nameOffset3 = (Graphics::screenSize.width * 3 / 4) - (name3.size() / 2);
	Graphics::write(nameOffset3, creditsY, name3);
}

void MenuScene::onEndLoop() {
}