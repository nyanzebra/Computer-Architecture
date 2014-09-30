#pragma once

#include <unordered_map>

#include "../utility/types.h"

class Logic {
public:
	//hashing
	static std::unordered_map<int, std::string>* m_hash_strings;

	//multi and single cycle
	
	static const int add(const int &a, const int &b);
	static const int sub(const int &a, const int &b);
	static const int mult(const int &a, const int &b);
	static const int div(const int &a, const int &b);

};