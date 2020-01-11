#include <algorithm>
#include <iostream>
#include <cstdio>
#include <exception>

#include "Core/Size.hpp"
#include "Core/Utilities.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::round;
using std::sscanf;
using std::string;
using std::vector;
using std::exception;
using std::runtime_error;

ScreenBuffer Graphics::buffer;
ScreenBuffer Graphics::oldBuffer;
Size Graphics::screenSize = Size(0, 0);

const Size Graphics::errorSize = Size(3, 3);
const Sprite Graphics::errorSprite = Utilities::newSprite(3, 3, '?');

void Graphics::clearBuffer() {
	for (int row = 0; row < screenSize.height; row++) {
		for (int column = 0; column < screenSize.width; column++) {
			oldBuffer[row][column] = buffer[row][column];
			buffer[row][column] = ' ';
		}
	}
}

void Graphics::initialise() {
	screenSize = System::getConsoleSize();

	buffer = Utilities::newSprite(screenSize.width, screenSize.height, ' ');
	oldBuffer = Utilities::newSprite(screenSize.width, screenSize.height, ' ');
}

void Graphics::draw(Rect rect, Sprite sprite) {
	//Se x è -20, ignorerà le prime 20 colonne dello sprite
	int minSpriteX = max(0, -(int)round(rect.position.x));
	int minSpriteY = max(0, -(int)round(rect.position.y));

	//Le ultime coordinate (escluse)
	int lastX = (int)round(rect.position.x) + rect.size.width;
	int lastY = (int)round(rect.position.y) + rect.size.height;

	//Quanto lo sprite fa overflow
	int overflowX = max(0, lastX - screenSize.width);
	int overflowY = max(0, lastY - screenSize.height);

	//Se x è 20 colonne oltre la dimensione, lui ignorerà le ultime 20 colonne dello sprite
	int maxSpriteX = rect.size.width - overflowX;
	int maxSpriteY = rect.size.height - overflowY;

	for (int y = minSpriteY; y < maxSpriteY; y++) {
		for (int x = minSpriteX; x < maxSpriteX; x++) {
			int spritePosition = y * rect.size.width + x;

			int screenX = (int)round(rect.position.x) + x;
			int screenY = (int)round(rect.position.y) + y;

			int screenPosition = screenY * screenSize.width + screenX;

			if (sprite[y][x] != ' ') {
				buffer[screenY][screenX] = sprite[y][x];
			}
		}
	}
}

void Graphics::draw(ptr_GameObject gameObject) {
	draw(gameObject->rect, gameObject->sprite);
}

void Graphics::redrawScreen() {
	System::clearScreen();
	for (int y = 0; y < screenSize.height; y++) {
		for (int x = 0; x < screenSize.width; x++) {
			cout << buffer[y][x];
		}
		if (y != screenSize.height) {
			cout << endl;
		}
	}
}

void Graphics::updateScreen() {
	for (int y = 0; y < screenSize.height; y++) {
		bool redraw = false;
		for (int x = 0; x < screenSize.width; x++) {
			if (oldBuffer[y][x] == buffer[y][x]) {
				//Termina il redraw (se non era già terminato)
				redraw = false;
			}
			else {
				if (!redraw) {
					//Se sta iniziando un redraw, sposta il cursore
					System::moveCursor(x, y);
				}
				redraw = true;

				cout << buffer[y][x];
			}
		}
	}

	//Sposta il cursore al fondo dello schermo
	System::moveCursor(screenSize.width - 1, screenSize.height - 1);
}

Sprite Graphics::parseSprite(vector<string> lines, Size& size) {
	Sprite sprite;

	//Esegui il parsing della prima linea
	if (lines.size() == 0) {
		throw runtime_error("File vuoto.");
	}

	int width;
	int height;
	sscanf_s(lines[0].c_str(), "%d;%d", &width, &height);

	size = Size(width, height);

	//Salta la prima riga
	for (int y = 1; y < height + 1; y++) {
		string row;
		for (int x = 0; x < width; x++) {
			row.push_back(lines[y][x]);
		}
		sprite.push_back(row);
	}

	return sprite;
}

Sprite Graphics::loadSpriteFromFile(string path, Size& size) {
	Sprite sprite;

	try {
		vector<string> fileContents = System::loadFile(path);
		sprite = Graphics::parseSprite(fileContents, size);
	}
	catch (exception e) {
#ifdef _DEBUG
		throw;
#else
		//Non interrompere l'esecuzione del codice, usa lo sprite di errore
		size = errorSize;
		sprite = Graphics::errorSprite;
#endif


	}

	return sprite;
}