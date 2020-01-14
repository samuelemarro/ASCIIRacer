#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> Sprite;
typedef std::vector<std::string> ScreenBuffer;
typedef ScreenBuffer* ptr_ScreenBuffer;
typedef std::vector<std::vector<bool>> CollisionMask;
typedef CollisionMask* ptr_CollisionMask;

const char IGNORE_CHAR = 1;
const char IGNORE_CHAR_FILE = ' ';