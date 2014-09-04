#pragma once

#include <string>
#include <vector>

#include "../utility/fileparser.h"

class Console { //singleton
public:

	static Console& instance() {

		static Console instance;

		m_continue = true;
		
		return instance;
	}

	//display
	inline void printHelp();
	void beginPrompt();
	void tokenize(const std::string& line);

	//input
	void parseInput();
private:
	Console() {};
	Console(Console const&);
	void operator=(Console const&);

	std::vector<std::string> m_command; //vector of user input

	FileParser m_fileparser; //handler for file io

	static bool m_continue; //determines whether console program should continue
};