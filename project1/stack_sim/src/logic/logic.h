#include <list>

typedef std::list<int> stack;

class Logic {
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
};

