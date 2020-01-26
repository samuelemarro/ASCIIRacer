#pragma once

#include <vector>
#include <string>

#include "Core/Cell.hpp"

typedef std::vector<std::vector<Cell>> Sprite;
typedef std::vector<std::vector<Cell>> ScreenBuffer;
typedef ScreenBuffer* ptr_ScreenBuffer;

/// <summary>	Il carattere usato dal motore per
/// 			indicare "nessun carattere". </summary>
const char IGNORE_CHAR = 0;

/// <summary>	Il carattere usato nei file per
/// 			indicare "nessun carattere". </summary>
const char IGNORE_CHAR_FILE = ' ';

/// <summary>	Il carattere usato nei file per
/// 			indicare "carattere speciale". </summary>
const char SPECIAL_CHAR_FILE = (char)138;