#include <vector>
#include <algorithm>

#include "Core/Size.hpp"
#include "Core/Typedefs.hpp"

using std::find;
using std::string;
using std::vector;

class Utilities
{
private:
	Utilities();

public:
	template <class InputIterator, class T>
	static bool isIn(InputIterator first, InputIterator last, const T& val)
	{
		return (find(first, last, val) != last);
	}

	static Sprite newSprite(int width, int height, char defaultValue) {
		vector<string> matrix;
		matrix.reserve(height);
		for (int y = 0; y < height; y++) {
			string row;
			row.reserve(width);
			for (int x = 0; x < width; x++) {
				row.push_back(defaultValue);
			}
			matrix.push_back(row);
		}

		return matrix;
	}
};