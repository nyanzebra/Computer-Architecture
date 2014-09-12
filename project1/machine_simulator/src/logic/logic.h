#pragma once

#include <unordered_map>

#include "../utility/types.h"

class Logic {
public:
	//hashing
	static std::unordered_map<int, std::string>* m_hash_strings;
	//stack machine add
	static const data_t add();
	//accum machine add
	static void add(const instruction_t& addr);
	//stack machine multiply
	static const data_t mult();
	//stack machine multiply
	static void mult(const instruction_t& addr);
	static int end();
	//print functions
	static void stack_print();
	static void accum_print();
};