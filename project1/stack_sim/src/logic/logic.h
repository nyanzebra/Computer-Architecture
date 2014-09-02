#include <list>
#include <iostream>

typedef std::list<int> stack;

class Logic {//TODO fix for memory address
public:
	static const int add(stack& s) {
		int i = s.back();
		s.pop_back();
		int j = s.back();
		s.pop_back();
		return i + j;
	}
	static const int mult(stack& s) {
		int i = s.back();
		s.pop_back();
		int j = s.back();
		s.pop_back();
		return i * j;
	}	
	static int end() {
		return 0;
	}
	static void print(stack& s) { 
		std::cout << s.back() << std::endl;
		s.pop_back();
	}
};

