#include "Key.hpp"
#include "KeyboardStatus.hpp"
#include "Utilities.hpp"

using std::vector;

KeyboardStatus::KeyboardStatus() : pressedKeys(vector<Key>()), downKeys(vector<Key>()), releasedKeys(vector<Key>()) {

}

KeyboardStatus::KeyboardStatus(vector<Key> pressedKeys, vector<Key> downKeys, vector<Key> releasedKeys) : pressedKeys(pressedKeys), downKeys(downKeys), releasedKeys(releasedKeys)
{
}

bool KeyboardStatus::isPressed(Key key)
{
	return Utilities::isIn(pressedKeys.begin(), pressedKeys.end(), key);
}
bool KeyboardStatus::isDown(Key key)
{
	return Utilities::isIn(downKeys.begin(), downKeys.end(), key);
}

bool KeyboardStatus::isReleased(Key key)
{
	return Utilities::isIn(releasedKeys.begin(), releasedKeys.end(), key);
}