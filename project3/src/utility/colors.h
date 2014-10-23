#pragma once

#include <ostream>

class ColorText
{
public:
	enum Code{
		RED			= 31,
		GREEN		= 32,
		BLUE		= 34,
		DEFAULT		= 39,
	};
	ColorText(Code color) : code(color) {}
	friend std::ostream& operator<<(std::ostream& os, const ColorText& color) { return os << "\033[" << color.code << "m"; }
	~ColorText() {}

private:
	Code code;
};