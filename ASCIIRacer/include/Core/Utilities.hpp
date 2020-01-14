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
};