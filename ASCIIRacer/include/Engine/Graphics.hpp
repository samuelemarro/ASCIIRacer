#include "Core/Rect.hpp"
#include "Core/Size.hpp"
#include "GameObjects/GameObject.hpp"

class Graphics {
private:
	Graphics();
	static char *buffer;
	static char* oldBuffer;
public:
	static Size screenSize;

	static char* loadSpriteFromFile();

	static void initialise();
	static void clearBuffer();
	static void draw(Rect rect, char sprite[]);
	static void draw(GameObject gameObject);
	static void redrawScreen();

	static void updateScreen();
};