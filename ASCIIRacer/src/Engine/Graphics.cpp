#include <algorithm>
#include <iostream>

#include "Core/Size.hpp"
#include "Core/Utilities.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::round;

char* Graphics::buffer;
char* Graphics::oldBuffer;
Size Graphics::screenSize = Size(0, 0);

void Graphics::clearBuffer() {

	for (int i = 0; i < screenSize.length(); i++) {
		oldBuffer[i] = buffer[i];
		buffer[i] = ' ';
	}
}

void Graphics::initialise() {
	screenSize = System::getConsoleSize();

	buffer = new char[screenSize.length()];
	oldBuffer = new char[screenSize.length()];
}

void Graphics::draw(Rect rect, char sprite[]) {
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

			if (sprite[spritePosition] != ' ') {
				buffer[screenPosition] = sprite[spritePosition];
			}
		}
	}
}

void Graphics::draw(GameObject gameObject) {
	draw(gameObject.rect, gameObject.sprite);
}

void Graphics::redrawScreen() {
	System::clearScreen();
	for (int y = 0; y < screenSize.height; y++) {
		for (int x = 0; x < screenSize.width; x++) {
			int position = y * screenSize.width + x;
			cout << buffer[position];
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
			int position = y * screenSize.width + x;

			if (oldBuffer[position] == buffer[position]) {
				//Termina il redraw (se non era già terminato)
				redraw = false;
			}
			else {
				if (!redraw) {
					//Se sta iniziando un redraw, sposta il cursore
					System::moveCursor(x, y);
				}
				redraw = true;

				cout << buffer[position];
			}
		}
	}

	//Sposta il cursore al fondo dello schermo
	System::moveCursor(screenSize.width - 1, screenSize.height - 1);
}