#include "Scenes/MenuScene.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/System.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/GameScene.hpp"

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
//Keyboard status;

void addOption(string name, ptr_Scene s) {
	options.push_back(pss(name, s));
}

void fetchOptions() {
	GameScene play;
	addOption("PLAY", &play);
	addOption("OPTIONS", NULL);
	addOption("CREDITS", NULL);
	addOption("EXIT", NULL);
}

void drawMenu() {
	System::moveCursor(marginX, marginY);
	cout << "ASCIIRacer";
	for (int i = 0; i < options.size(); i++) {
		System::moveCursor(marginX, marginY + (i + 1) * distanceY);
		cout << options[i].first;
	}
}

void MenuScene::onStart(){
	fetchOptions();
	drawMenu();
}

void MenuScene::onLoop() {

}

void MenuScene::onGraphics() {

}

void MenuScene::onEndLoop() {

}