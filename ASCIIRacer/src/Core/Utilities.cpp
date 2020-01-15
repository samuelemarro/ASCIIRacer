#include "Core/Utilities.hpp"
#include <cctype>

int Utilities::hexToNumber(char hex)
{
	int value = -1;
	hex = tolower(hex);

	if (hex >= 'a' && hex <= 'f') {
		value = (hex - 'a') + 10;
	}
	else if (hex >= '0' && hex <= '9') {
		value = hex - '0';
	}

	return value;
}
