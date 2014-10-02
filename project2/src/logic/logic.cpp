#include <iostream>
#include <array>

#include "logic.h"
#include "../memory/memory.h"

std::unordered_map<int, std::string>* Logic::m_hash_strings = new std::unordered_map<int, std::string>();

// a is always first source and b is always second source.

const int Logic::add(const int &a, const int &b) {
	return a + b;
}

const int Logic::sub(const int &a, const int &b) {
	return a - b;
}

const int Logic::div(const int &a, const int &b) {
	return a / b;
}

const int Logic::mult(const int &a, const int &b) {
	return a * b;
}
