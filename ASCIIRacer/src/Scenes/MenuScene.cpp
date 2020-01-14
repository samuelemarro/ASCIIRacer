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
	ptr_Scene adder = new GameScene();
	addOption("PLAY", adder);
	//se voglio aggiungere altra scene faccio adder = new nomeScene; e poi addOption("option name", adder);
	addOption("OPTIONS", NULL);
	addOption("CREDITS", NULL);
	//EXIT opzione deve essere ultima aggiunta
	addOption("EXIT", NULL);
}

void MenuScene::drawMenu() {
	Graphics::write(marginX, marginY, "ASCIIRacer");
	for (int i = 0; i < options.size(); i++) {
		Graphics::write((float)marginX, (float)marginY + (i + 1) * (float)distanceY, options[i].first);
	}
}

void MenuScene::moveCursor(bool down) {
	if (down && (cursor<options.size()-1)) cursor++;
	else if(!down && cursor>0) cursor--;
}

void MenuScene::onStart(){
	fetchOptions();
}

void MenuScene::onLoop() {
	if (status.isPressed(Key::Down)) moveCursor(true);
	else if (status.isPressed(Key::Up)) moveCursor(false);

	status = Keyboard::currentStatus;
	bool change = false;
	if (status.isPressed(Key::Confirm)) change = true;
	if (options[cursor].second != NULL && change) GameEngine::changeScene(options[cursor].second);
	else if (cursor == options.size() - 1 && change) exit(EXIT_SUCCESS);
}

void MenuScene::onGraphics() {
	drawMenu();
	Graphics::write((float)marginX - 1, (float)marginY + (cursor + 1) * (float)distanceY, " ");
	Graphics::write((float)marginX - 1, (float)marginY + (cursor + 1) * (float)distanceY, ">");
}

void MenuScene::onEndLoop() {

}