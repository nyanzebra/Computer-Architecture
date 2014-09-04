#include <vector>

template<typename T>
std::vector<T> makeVector(const int& size) {
	std::vector<T> v(size);
	return v;
}