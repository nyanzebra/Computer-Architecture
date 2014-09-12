#include "console/console.h"

int main(int argc, char const *argv[]) {

	Console::instance().printHelp();
	Console::instance().beginPrompt();	

	return 0;
}