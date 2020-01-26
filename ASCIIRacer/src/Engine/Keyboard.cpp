#include <map>
#include <string>

#include "Engine/System.hpp"
#include "Engine/Key.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/KeyboardStatus.hpp"

#include <algorithm>
#include <iostream>
#include <Windows.h>

using std::map;
using std::vector;
using std::string;
using std::find;

KeyboardStatus Keyboard::currentStatus = KeyboardStatus();
map<int, Key> Keyboard::keyBindings = { {'W', Key::Up}, {VK_UP, Key::Up},
										{'A', Key::Left}, {VK_LEFT, Key::Left},
										{'S', Key::Down}, {VK_DOWN, Key::Down},
										{'D', Key::Right}, {VK_RIGHT, Key::Right},
										{13, Key::Confirm} };

vector<Key> Keyboard::getDownKeys() {
	vector<Key> downKeys;
	for (auto pair : Keyboard::keyBindings) {
		if (System::keyIsDown(pair.first)) {
			if (find(downKeys.begin(), downKeys.end(), pair.second) == downKeys.end()) {
				downKeys.push_back(pair.second);
			}
		}
	}

	return downKeys;
}

void Keyboard::updateStatus()
{
	vector<Key> inputKeys = Keyboard::getDownKeys();

	vector<Key> pressed;
	vector<Key> down;
	vector<Key> released;

	//Identifica i pressed e i down
	for (auto inputKey : inputKeys)
	{
		if (!Keyboard::currentStatus.isDown(inputKey))
		{
			pressed.push_back(inputKey);
		}
		down.push_back(inputKey);
	}

	//Identifica i released
	for (auto downKey : currentStatus.downKeys)
	{
		if (find(inputKeys.begin(), inputKeys.end(), downKey) == inputKeys.end())
		{
			released.push_back(downKey);
		}
	}

	Keyboard::currentStatus = KeyboardStatus(pressed, down, released);
}