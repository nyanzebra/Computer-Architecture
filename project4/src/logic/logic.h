#pragma once

#include <unordered_map>

#include "../utility/types.h"

template<typename T>
class Logic {
public:
	//multi and single cycle
	static const T add(const T &a, const T &b) { return a + b; }
	static const T sub(const T &a, const T &b) { return a - b; }
	static const T mult(const T &a, const T &b) { return a * b; }
	static const T div(const T &a, const T &b) { return a / b; }
};
