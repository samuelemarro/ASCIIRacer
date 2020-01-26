#include <algorithm>

#include "Engine/Key.hpp"
#include "Engine/KeyboardStatus.hpp"

using std::vector;
using std::find;

KeyboardStatus::KeyboardStatus() {
	this->pressedKeys = vector<Key>();
	this->downKeys = vector<Key>();
	this->releasedKeys = vector<Key>();
}

KeyboardStatus::KeyboardStatus(vector<Key> pressedKeys, vector<Key> downKeys, vector<Key> releasedKeys) : pressedKeys(pressedKeys), downKeys(downKeys), releasedKeys(releasedKeys)
{
}

bool KeyboardStatus::isPressed(Key key)
{
	return find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}
bool KeyboardStatus::isDown(Key key)
{
	return find(downKeys.begin(), downKeys.end(), key) != downKeys.end();
}

bool KeyboardStatus::isReleased(Key key)
{
	return find(releasedKeys.begin(), releasedKeys.end(), key) != releasedKeys.end();
}