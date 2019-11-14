#include <string>

#include "Core/Rect.hpp"
#include "Core/Size.hpp"
#include "Core/Typedefs.hpp"
#include "GameObjects/GameObject.hpp"

class Graphics {
private:
	Graphics();
	static ScreenBuffer buffer;
	static ScreenBuffer oldBuffer;

	static Sprite parseSprite(std::vector<std::string> lines, Size& size);

	static const Size errorSize;
	static const Sprite errorSprite;
public:
	static Size screenSize;

	static Sprite loadSpriteFromFile(std::string path, Size& size);

	static void initialise();
	static void clearBuffer();
	static void draw(Rect rect, Sprite sprite);
	static void draw(ptr_GameObject gameObject);
	static void redrawScreen();

	static void updateScreen();
};