#include <map>
#include <string>

#include "Engine/System.hpp"
#include "Engine/Key.hpp"
#include "Engine/Keyboard.hpp"
#include "KeyboardStatus.hpp"

#include "Utilities.hpp"

#include <iostream>

using std::map;
using std::vector;
using std::string;

KeyboardStatus Keyboard::currentStatus = KeyboardStatus();
map<string, Key> Keyboard::keyBindings = { {"w", Key::Up}, {"a", Key::Left}, {"s", Key::Down}, {"d", Key::Right} };

char Keyboard::readKeyboard()
{
	if (System::keyPressed())
	{
		return System::getCharacter();
	}
	else
	{
		return '\0';
	}
}

string Keyboard::readAll()
{
	string fullString;

	char c;
	do
	{
		c = readKeyboard();
		if (c != '\0')
		{
			fullString.push_back(c);
		}
	} while (c != '\0');

	return fullString;
}

vector<Key> Keyboard::parseKeys(string input)
{
	vector<Key> keys;
	string currentString;
	while (!input.empty())
	{
		char c = input.at(0);
		input.erase(0);

		currentString.push_back(c);

		map<string, Key>::iterator it = Keyboard::keyBindings.begin();

		bool match = false;
		while (it != Keyboard::keyBindings.end() && !match)
		{
			if (it->first.compare(currentString) == 0)
			{
				Key key = Keyboard::keyBindings.at(it->first);
				keys.push_back(key);
				currentString.clear();

				match = true;
			}
			it++;
		}
	}

	return keys;
}

void Keyboard::updateStatus()
{
	string input = readAll();
	vector<Key> inputKeys = parseKeys(input);

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
		if (!Utilities::isIn(inputKeys.begin(), inputKeys.end(), downKey))
		{
			released.push_back(downKey);
		}
	}


	Keyboard::currentStatus = KeyboardStatus(pressed, down, released);
}