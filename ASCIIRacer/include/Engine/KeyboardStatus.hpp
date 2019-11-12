#pragma once

#include <vector>

#include "Key.hpp"

class KeyboardStatus
{
public:
	std::vector<Key> pressedKeys;
	std::vector<Key> downKeys;
	std::vector<Key> releasedKeys;
	//Possibile ottimizzazione: pressedKeys_ e stillDownKeys_


    bool isPressed(Key key);
    bool isDown(Key key);
    bool isReleased(Key key);

	KeyboardStatus();
    KeyboardStatus(std::vector<Key> pressedKeys, std::vector<Key> downKeys, std::vector<Key> releasedKeys);
};