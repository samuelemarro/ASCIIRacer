#include <vector>
#include <algorithm>

#include "Core/Size.hpp"

using std::find;

class Utilities
{
private:
    Utilities();

public:
    template <class InputIterator, class T>
    static bool isIn(InputIterator first, InputIterator last, const T &val)
    {
        return (find(first, last, val) != last);
    }

	template <class T>
	static void fill2D(T* array_, Size size, T content) {
		for (int y = 0; y < size.height; y++) {
			for (int x = 0; x < size.width; x++) {
				int position = y * size.width + x;
				array_[position] = content;
			}
		}
	}
};