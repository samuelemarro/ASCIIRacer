#include <vector>
#include <algorithm>

#include "Core/Size.hpp"

using std::find;
using std::vector;

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
	static void fill2D(vector<vector<T>> array_, T content) {
		for (int y = 0; y < array_.size(); y++) {
			if (array_[y].size() > 0) {
				for (int x = 0; x < array_[y].size(); x++) {
					array_[y][x] = content;
				}
			}
		}
	}

	template <class T>
	static vector<vector<T>> newMatrix(int width, int height, T defaultValue) {
		vector<vector<T>> matrix;
		matrix.reserve(height);
		for (int y = 0; y < height; y++) {
			vector<T> row;
			row.reserve(width);
			for (int x = 0; x < width; x++) {
				row.push_back(defaultValue);
			}
			matrix.push_back(row);
		}

		return matrix;
	}
};