#pragma once

#include <string>
#include <map>
#include "Key.hpp"
#include "KeyboardStatus.hpp"

class Keyboard
{
private:
	static std::vector<Key> getDownKeys();

	Keyboard();

public:
	/**
	 * @brief La mappa da caratteri a tasto.
	 * Usiamo stringhe perché alcuni tasti (es. frecce)
	 * vengono espresse come sequenza di caratteri.
	 */
	static KeyboardStatus currentStatus;
	static std::map<int, Key> keyBindings;
	static void updateStatus();
};