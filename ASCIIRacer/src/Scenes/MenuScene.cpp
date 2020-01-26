#include "Scenes/MenuScene.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Graphics.hpp"


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
	Rect rect = Rect(Point2D(titleOffset, 1.0f), size);

	this->titleRect = rect;
}

void MenuScene::onLoop() {
	auto status = Keyboard::currentStatus;
	if (status.isPressed(Key::Down)) moveCursor(true);
	else if (status.isPressed(Key::Up)) moveCursor(false);

	bool change = false;
	if (status.isPressed(Key::Confirm)) change = true;
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

	vector<string> names = { "Samuele Marro", "Edoardo Merli", "Filip Radovic" };

	for (int i = 0; i < 3; i++) {
		int nameOffset = (Graphics::screenSize.width * (i + 1) / 4) - (names[i].size() / 2);
		Graphics::write(nameOffset, creditsY, names[i]);
	}
}