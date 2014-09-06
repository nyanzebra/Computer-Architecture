#ifndef PCH_H
#include "pch.h"
#endif

int main(int argc, char const *argv[]) {

	Console::instance().printHelp();
	Console::instance().beginPrompt();	

	return 0;
}