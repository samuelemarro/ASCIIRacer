#pragma once

#include <string>
#include <map>
#include "Key.hpp"
#include "KeyboardStatus.hpp"

class Keyboard
{
private:
    static std::vector<Key> currentDownKeys;

	static char readKeyboard();
	static std::string readAll();
	static std::vector<Key> parseKeys(std::string input);

    Keyboard();

public:
    /**
     * @brief La mappa da caratteri a tasto.
     * Usiamo stringhe perché alcuni tasti (es. frecce)
     * vengono espresse come sequenza di caratteri.
     */
    static std::map<std::string, Key> keyBindings;
    static KeyboardStatus *getStatus();
};