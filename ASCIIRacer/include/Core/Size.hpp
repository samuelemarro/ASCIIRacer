#pragma once

/// <summary>	Rappresenta una dimensione. </summary>

class Size {
public:

	/// <summary>	La larghezza. </summary>
	int width;

	/// <summary>	L'altezza. </summary>
	int height;

	/// <summary>	Costruttore di default. </summary>

	Size();

	/// <summary>	Costruttore completo. </summary>
	///
	/// <param name="width">	La larghezza. </param>
	/// <param name="height">	L'altezza. </param>

	Size(int width, int height);
};