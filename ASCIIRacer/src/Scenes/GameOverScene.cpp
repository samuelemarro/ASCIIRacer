#include "Scenes/GameOverScene.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Graphics.hpp"


using namespace std;
typedef pair<string, string> pss;

const int marginY = 2;
const int marginX = 30;
const int distanceY = 2;

void GameOverScene::addOption(string name, string scene) {
	this->options.push_back(pss(name, scene));
}

void GameOverScene::fetchOptions() {
	addOption("NEW GAME", "GameScene");
	addOption("MAIN MENU", "MenuScene");
}

void GameOverScene::drawMenu(int xOffset, int yOffset) {
	//Graphics::write(xOffset, yOffset, "ASCIIRacer");
	for (int i = 0; i < this->options.size(); i++) {
		Graphics::write((float)xOffset, (float)yOffset + (i + 1) * (float)distanceY, this->options[i].first);
	}
}

void GameOverScene::moveCursor(bool down) {
	if (down && (this->cursor < this->options.size() - 1)) this->cursor++;
	else if (!down && this->cursor > 0) this->cursor--;
}

void GameOverScene::onStart() {
	fetchOptions();
	Size size;
	this->gameOverSprite = Graphics::loadSpriteFromFile(System::getExecutableDirectory() + "/sprites/GameOverScreen.txt", size);
	int titleXOffset = (Graphics::screenSize.width - size.width) / 2;
	int titleYOffset = 3;

	this->gameOverRect = Rect(Point2D(titleXOffset, titleYOffset), size);
}

void GameOverScene::onLoop() {
	auto status = Keyboard::currentStatus;

	if (status.isPressed(Key::Down)) {
		moveCursor(true);
	}
	else if (status.isPressed(Key::Up)) {
		moveCursor(false);
	}

	bool change = false;
	if (status.isPressed(Key::Confirm)) {
		change = true;
	}
	if (this->options[this->cursor].second != " " && change) {
		GameEngine::changeScene(this->options[this->cursor].second);
	}
}

void GameOverScene::onGraphics() {
	Graphics::draw(this->gameOverRect, this->gameOverSprite);

	int maxLength = -1;

	for (pss pair : this->options) {
		if ((int)pair.first.size() > maxLength) {
			maxLength = pair.first.size();
		}
	}

	float scoreOffsetY = this->gameOverRect.position.y + this->gameOverRect.size.height + 1;
	Graphics::writeCentered(scoreOffsetY, "Best Score:");
	string scoreText = std::to_string(this->bestScore);
	if (scoreText.size() % 2 == 0) {
		scoreText += " ";
	}
	Graphics::writeCentered(scoreOffsetY + 2, scoreText);

	float textOffsetX = (Graphics::screenSize.width - maxLength) / 2;
	float textOffsetY = scoreOffsetY + 4;

	drawMenu(textOffsetX, textOffsetY);
	Graphics::write((float)textOffsetX - 1, (float)textOffsetY + (this->cursor + 1) * (float)distanceY, ">");
}