#include <algorithm>
#include <iostream>

#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::sscanf;
using std::string;
using std::vector;
using std::exception;
using std::runtime_error;

ScreenBuffer Graphics::buffer;
ScreenBuffer Graphics::oldBuffer;
Size Graphics::screenSize = Size(0, 0);

const Size Graphics::errorSize = Size(3, 3);
const Sprite Graphics::errorSprite = Graphics::newSprite(3, 3, '?');

void Graphics::clearBuffer() {
	for (int row = 0; row < screenSize.height; row++) {
		for (int column = 0; column < screenSize.width; column++) {
			oldBuffer[row][column] = buffer[row][column];
			buffer[row][column] = Cell(' ');
		}
	}
}

void Graphics::initialise() {
	screenSize = System::getConsoleSize();

	buffer = Graphics::newSprite(screenSize.width, screenSize.height, ' ');
	oldBuffer = Graphics::newSprite(screenSize.width, screenSize.height, ' ');
}

void Graphics::draw(Rect rect, Sprite sprite) {
	//Se x è -20, ignorerà le prime 20 colonne dello sprite

	int minSpriteX = max(0, -(int)(rect.position.x));
	int minSpriteY = max(0, -(int)(rect.position.y));

	//Le ultime coordinate (escluse)
	int lastX = (int)(rect.position.x) + rect.size.width;
	int lastY = (int)(rect.position.y) + rect.size.height;

	//Quanto lo sprite fa overflow
	int overflowX = max(0, lastX - screenSize.width);
	int overflowY = max(0, lastY - screenSize.height);

	//Se x è 20 colonne oltre la dimensione, lui ignorerà le ultime 20 colonne dello sprite
	int maxSpriteX = rect.size.width - overflowX;
	int maxSpriteY = rect.size.height - overflowY;

	for (int y = minSpriteY; y < maxSpriteY; y++) {
		for (int x = minSpriteX; x < maxSpriteX; x++) {
			int spritePosition = y * rect.size.width + x;

			int screenX = (int)(rect.position.x) + x;
			int screenY = (int)(rect.position.y) + y;

			int screenPosition = screenY * screenSize.width + screenX;

			if (sprite[y][x].character != IGNORE_CHAR) {
				buffer[screenY][screenX] = sprite[y][x];
			}
		}
	}
}

void Graphics::draw(ptr_GameObject gameObject) {
	draw(gameObject->rect, gameObject->sprite);
}

void Graphics::write(float x, float y, std::string text)
{
	//Crea uno sprite di larghezza text.length() e altezza 1
	//contenente il testo
	Sprite s = Sprite();
	s.push_back(vector<Cell>());
	for (int i = 0; i < text.length(); i++) {
		s[0].push_back(Cell(text[i]));
	}

	Rect rect = Rect(x, y, text.length(), 1);
	Graphics::draw(rect, s);
}

void Graphics::writeCentered(float y, std::string text)
{
	float x = (Graphics::screenSize.width - text.size()) / 2;
	Graphics::write(x, y, text);
}

void Graphics::redrawScreen() {
	System::clearScreen();
	for (int y = 0; y < screenSize.height; y++) {
		for (int x = 0; x < screenSize.width; x++) {
			System::setTextColor(buffer[y][x].foreground, buffer[y][x].background);
			cout << buffer[y][x].character;
		}
		if (y != screenSize.height) {
			cout << endl;
		}
	}
}

void Graphics::updateScreen() {
	Color lastForeground = Color::No_Color;
	Color lastBackground = Color::No_Color;
	System::setTextColor(Color::No_Color, Color::No_Color);

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

				if (buffer[y][x].foreground != lastForeground || buffer[y][x].background != lastBackground) {
					System::setTextColor(buffer[y][x].foreground, buffer[y][x].background);
					lastForeground = buffer[y][x].foreground;
					lastBackground = buffer[y][x].background;
				}

				//Il metodo più veloce per stampare un carattere
				cout << buffer[y][x].character;
			}
		}
	}

	//Sposta il cursore al fondo dello schermo
	System::moveCursor(screenSize.width - 1, screenSize.height - 1);
}

Sprite Graphics::newSprite(int width, int height, char defaultValue) {
	Sprite sprite;
	sprite.reserve(height);
	for (int y = 0; y < height; y++) {
		vector<Cell> row = vector<Cell>();
		row.reserve(width);
		for (int x = 0; x < width; x++) {
			row.push_back(Cell(defaultValue));
		}
		sprite.push_back(row);
	}

	return sprite;
}

Sprite Graphics::parseSprite(vector<string> lines, Size& size) {
	Sprite sprite;

	//Esegui il parsing della prima linea
	if (lines.size() == 0) {
		throw runtime_error("File vuoto.");
	}

	int width;
	int height;
	int nvars = sscanf_s(lines[0].c_str(), "%d;%d", &width, &height);

	size = Size(width, height);

	int currentLine;

	//Salta la prima riga
	for (currentLine = 1; currentLine < height + 1; currentLine++) {
		vector<Cell> row = vector<Cell>();
		for (int x = 0; x < width; x++) {
			if (lines[currentLine][x] == IGNORE_CHAR_FILE) {
				row.push_back(Cell(IGNORE_CHAR));
			}
			else if (lines[currentLine][x] == SPECIAL_CHAR_FILE) {
				//Carattere speciale
				string substr = lines[currentLine].substr(x + 1, x + 4);
				int code;
				sscanf_s(substr.c_str(), "%d", &code);
				row.push_back(Cell(code));
				x += 3;
			}
			else {
				row.push_back(Cell(lines[currentLine][x]));
			}
		}
		sprite.push_back(row);
	}

	while (currentLine < lines.size()) {
		//Mask: conta come collisione se il carattere non è IGNORE_CHAR_FILE
		if (lines[currentLine].find("MASK") != string::npos) {
			int startingPoint = currentLine + 1;
			for (int y = 0; y < height; y++) {
				vector<bool> row;
				for (int x = 0; x < width; x++) {
					sprite[y][x].collision = (lines[startingPoint + y][x] != IGNORE_CHAR_FILE);
				}
			}
			currentLine = startingPoint + height;
		}
		else if (lines[currentLine].find("FOREGROUND") != string::npos) {
			int startingPoint = currentLine + 1;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (lines[i + startingPoint][j] != IGNORE_CHAR_FILE) {
						sprite[i][j].foreground = Graphics::hexToColor(lines[i + startingPoint][j]);
					}
				}
			}
			currentLine = startingPoint + height;
		}
		else if (lines[currentLine].find("BACKGROUND") != string::npos) {
			int startingPoint = currentLine + 1;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (lines[i + startingPoint][j] != IGNORE_CHAR_FILE) {
						sprite[i][j].background = Graphics::hexToColor(lines[i + startingPoint][j]);
					}
				}
			}
			currentLine = startingPoint + height;
		}
		else {
			currentLine++;
		}
	}

	return sprite;
}

Color Graphics::hexToColor(char hex)
{
	int value = -1;
	hex = tolower(hex);

	if (hex >= 'a' && hex <= 'f') {
		value = (hex - 'a') + 10;
	}
	else if (hex >= '0' && hex <= '9') {
		value = hex - '0';
	}

	return (Color)value;
}

Sprite Graphics::loadSpriteFromFile(string path, Size& size) {
	Sprite sprite;

	try {
		vector<string> fileContents = System::loadFile(path);
		sprite = Graphics::parseSprite(fileContents, size);
	}
	catch (exception e) {
#ifdef _DEBUG
		cout << e.what();
#else
		//Non interrompere l'esecuzione del codice, usa lo sprite di errore
		size = errorSize;
		sprite = Graphics::errorSprite;
#endif
	}

	return sprite;
}