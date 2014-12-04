#include <iostream>

#include "console.h"

#include "../machine/generalpurposeregistermachine.h"

//maybe more error messages?
#define input_invalid "ERROR: Invalid command entered. Type help for options. "
#define need_file "ERROR: need to specify a file to open. "
#define need_dir "ERROR: need to specify a directory to open. "
#define need_args "ERROR: please supply the proper flags for function: "
#define too_many_args "ERROR: too many flags were selected or too many arguments."

bool Console::m_continue = false;

//initial display
void Console::printHelp() {
	std::cout << "\nWelcome to machine simulator!\n\n"
			  << "commands:\n"
			  << "help\t\t\t display commands\n"
			  << "open\t\t\t takes a file argument\n"
			  << "switch\t\t\t changes funtion units for piping\n"
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
	bool is_path = false;
	for (char c : line) { // adds command and other info to vector
		if (is_path) {
			if (c != '"') { //this part is for getting paths with spaces in them
				temp += c;
			} else {
				m_command.push_back(temp);
				temp = "";
				is_path = false;
			}
		}
		if (c == '"') {
			is_path = true;
		}
		if (c == ' ' && !is_path) { //for everything else this gets it
			m_command.push_back(temp);
			temp = "";
		}else if (!is_path) {
			temp += c;
		}
	}

	if (temp.size() > 0) { //if only one command then this catches that and adds command to vector
		m_command.push_back(temp);
	}
}

// take user command and try to operate on that input
void Console::parseInput() {
	std::string _arg0, _arg1;

	if (m_command.size() > 0) {
		_arg0 = m_command[0]; //terminal command all args after are flags or content
	} else {
		std::cout << input_invalid << std::endl; //blank input is wrong input
	}

	if (m_command.size() > 1) {
		_arg1 = m_command[1]; //if we have more than one argument
	}

	//decide what to do based on user input
	if (_arg0 == "open") {
		if (m_command.size() > 1) {
			Compiler c = Compiler(m_fileparser.readFile(_arg1));
			c.compile();
		} else {
			std::cout << input_invalid << need_file << std::endl; //if don't specify file
		}
	} else if (_arg0 == "test") {
		m_fileparser.setDirectory("C:/Users/Robert/Documents/GitHub/Computer-Architecture/project4/assembly/");
		Compiler c = Compiler(m_fileparser.readFile("lab4b.s"));
		c.compile();
		Base_Machine* am = new GPR_Machine();
		am->begin();
	} else if (_arg0 == "switch") {
		if (m_command.size() == 1) {
			Base_Machine::setPipeline();
		} else {
			std::cout << input_invalid << std::endl;
		}
	} else if (_arg0 == "dir") {
		if (m_command.size() == 2) {
			m_fileparser.setDirectory(_arg1);
		} else {
			std::cout << input_invalid << need_dir << std::endl;
		}
	} else if (_arg0 == "file") {
		if (m_command.size() == 1) {
				std::cout << m_fileparser.getFilename() << std::endl;
				m_fileparser.printContents();
		} else {
			std::cout << input_invalid << std::endl;
		} 
	} else if (_arg0 == "start" && !m_fileparser.isEmpty()) {
		if (m_command.size() == 1) {
			Base_Machine* am = new GPR_Machine();
			am->begin();
		} else {
			std::cout << input_invalid << need_file << std::endl;
		}
	} else if (_arg0 == "help") {
		printHelp();
	} else if (_arg0 == "quit") {
		m_continue = false;
	} else {
		std::cout << input_invalid << std::endl;
	}
}
