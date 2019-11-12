#include "Key.hpp"
#include "KeyboardStatus.hpp"
#include "Utilities.hpp"

using std::vector;

KeyboardStatus::KeyboardStatus(vector<Key> pressedKeys, vector<Key> downKeys, vector<Key> releasedKeys) : pressedKeys_(pressedKeys), downKeys_(downKeys), releasedKeys_(releasedKeys)
{
}

bool KeyboardStatus::isPressed(Key key)
{
	return Utilities::isIn(pressedKeys_.begin(), pressedKeys_.end(), key);
}
bool KeyboardStatus::isDown(Key key)
{
	return Utilities::isIn(downKeys_.begin(), downKeys_.end(), key);
}

bool KeyboardStatus::isReleased(Key key)
{
	return Utilities::isIn(releasedKeys_.begin(), releasedKeys_.end(), key);
}