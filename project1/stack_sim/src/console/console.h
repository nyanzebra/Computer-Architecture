#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../utility/fileparser.h"

#define input_invalid "Invalid command entered. Type help for options."

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

bool Console::m_continue = false;

void Console::printHelp() {
	std::cout << "\nWelcome to machine simulator!\n\n"
			  << "arguments:\n"
			  << "-s --stack\t\t implement stack machine used with start command\n"
			  << "-a --accum\t\t implement accumulator machine used with start command\n"
			  << "commands:\n"
			  << "help\t\t\t display commands\n"
			  << "open\t\t\t takes a file argument\n"
			  << "start\t\t\t will execute file\n"
			  << "dir\t\t\t takes a directory path argument\n"
			  << "file\t\t\t will display what file is currently being used\n"
			  << "quit\t\t\t will exit the program\n"
			  << std::endl;		 
}

// starts the console program
void Console::beginPrompt() {
	while (m_continue) {
		
		if (m_command.size() > 0) {
			m_command.clear();
		}

		std::string input;
		std::cout << "> ";
		std::getline(std::cin,input);
		tokenize(input);
		parseInput();
	}
}

//split up string input into words
void Console::tokenize(const std::string& line) {
	std::string temp = "";

	for (char c : line) { // adds command and other info to vector
		if (c == ' ') {
			m_command.push_back(temp);
			temp = "";
		} else {
			temp += c;
		}
	}

	if (temp.size() > 0) { //if only one command then this catches that and adds command to vector
		m_command.push_back(temp);
	}
}

// take user command and try to operate on that input
void Console::parseInput() {
	std::string _arg0 = m_command[0]; //terminal command all args after are flags or content

	if (_arg0 == "open") {
		if (m_command.size() > 1) {
			m_fileparser.readFile(m_command[1]);
		} else {
			std::cout << input_invalid << std::endl;
		}
	} else if (_arg0 == "dir") {
		if (m_command.size() == 2) {
			m_fileparser.setDirectory(m_command[1]);
		} else {
			std::cout << input_invalid << std::endl;
		}
	} else if (_arg0 == "file") {
		if (m_command.size() == 1) {
				std::cout << m_fileparser.getFilename() << std::endl;
				m_fileparser.printContents();
		} else {
			std::cout << input_invalid << std::endl;
		} 
	} else if (_arg0 == "start" && !m_fileparser.isEmpty()) {

	} else if (_arg0 == "help") {
		printHelp();
	} else if (_arg0 == "quit") {
		m_continue = false;
	} else {
		std::cout << input_invalid << std::endl;
	}
}