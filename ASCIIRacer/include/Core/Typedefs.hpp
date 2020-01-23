#pragma once

#include <vector>
#include <string>

#include "Core/Cell.hpp"

typedef std::vector<std::vector<Cell>> Sprite;
typedef std::vector<std::vector<Cell>> ScreenBuffer;
typedef ScreenBuffer* ptr_ScreenBuffer;

//Il carattere usato dal motore per indicare "nessun carattere"
const char IGNORE_CHAR = 0;
//Il carattere usato nei file per indicare "nessun carattere"
const char IGNORE_CHAR_FILE = ' ';