#include "Scenes/MenuScene.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/System.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/GameScene.hpp"
#include "Engine/GameEngine.hpp"

#include "windows.h"
#include <utility>
#include <cstdlib>
#include <iostream>

using namespace std;
typedef pair<string, ptr_Scene> pss;

vector<pss> options;
const int marginY = 2;
const int marginX = 30;
const int distanceY = 2;
int cursor = 0;
KeyboardStatus status;

void MenuScene::addOption(string name, ptr_Scene s) {
	options.push_back(pss(name, s));
}

void MenuScene::fetchOptions() {
	ptr_Scene adder = new GameScene;
	addOption("PLAY", adder);
	//se voglio aggiungere altra scene faccio adder = new nomeScene; e poi addOption("option name", adder);
	addOption("OPTIONS", NULL);
	addOption("CREDITS", NULL);
	addOption("EXIT", NULL);
}

void MenuScene::drawMenu() {
	System::moveCursor(marginX, marginY);
	cout << "ASCIIRacer";
	for (int i = 0; i < options.size(); i++) {
		System::moveCursor(marginX, marginY + (i + 1) * distanceY);
		cout << options[i].first;
	}
}

void MenuScene::moveCursor(bool down) {
	System::moveCursor(marginX - 1, marginY + (cursor + 1) * distanceY);
	printf("%c", ' ');
	if (down && (cursor+1)<options.size()) cursor++;
	else if(!down && cursor>0) cursor--;
	System::moveCursor(marginX - 1, marginY + (cursor + 1) * distanceY);
	cout << '>';
}

void MenuScene::onStart(){
	fetchOptions();
	drawMenu();
	System::moveCursor(marginX - 1, marginY+distanceY);
	cout << '>';
}

void MenuScene::onLoop() {
	status = Keyboard::currentStatus;
	ptr_Scene option_selected = NULL;
	if (status.isPressed(Key::Down)) moveCursor(true);
	else if (status.isPressed(Key::Up)) moveCursor(false);
	if (status.isPressed(Key::Confirm)) option_selected = options[cursor].second;
	if (option_selected) GameEngine::changeScene(option_selected); //<-------questo e' da modificare
}

void MenuScene::onGraphics() {

}

void MenuScene::onEndLoop() {

}