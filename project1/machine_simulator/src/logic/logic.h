#pragma once

#include <string>

class Logic {//TODO fix for memory address
public:
	//stack machine add
	static const int add();
	//accum machine add
	static void add(const std::string& s);
	//stack machine multiply
	static const int mult();
	//stack machine multiply
	static void mult(const std::string& s);
	static int end();
	static void stack_print();
	static void accum_print();
};

