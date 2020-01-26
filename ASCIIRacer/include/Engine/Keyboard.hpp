#pragma once

#include <string>
#include <map>
#include "Key.hpp"
#include "KeyboardStatus.hpp"

/// <summary>	Gestisce la tastiera. </summary>

class Keyboard
{
private:

	/// <summary>	Restituisce le chiavi virtuali
	/// 			al momento premute. </summary>
	///
	/// <returns>	Il vettore di chiavi virtuali. </returns>

	static std::vector<Key> getDownKeys();

	/// <summary>	Costruttore di default (privato). </summary>

	Keyboard();

public:

	/// <summary>	Lo stato attuale della tastiera. </summary>
	static KeyboardStatus currentStatus;

	/// <summary>	I binding tra tasti fisici e tasti virtuali. </summary>
	static std::map<int, Key> keyBindings;

	/// <summary>	Aggiorna lo stato della tastiera. </summary>

	static void updateStatus();
};