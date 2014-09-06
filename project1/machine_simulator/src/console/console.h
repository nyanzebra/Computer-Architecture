#pragma once

//robert baldwin
//the console class operates as a gui for easy execution and project demonstration
//this is a singleton for if we decide to reset or make another console
//we can not worry about the old console as it is deleted
//this could be useful if we build on this project and would like a clear function for console
//then everything gets deleted and we can start over

#ifndef PCH_H
#include "../pch.h"
#endif

class Console { //singleton
public:

	static Console& instance() {//always returns a new instance

		static Console instance;

		m_continue = true;
		
		return instance;
	}

	//display
	inline void printHelp(); //probably already inlined by compiler but we should be safe and do it anyway
	void beginPrompt(); //initiate the gui!
	void tokenize(const std::string& line); //split strings into words

	//input
	void parseInput();//figure out what command user wants
private:
	//no touchy!!!
	Console() {};
	Console(Console const&);
	void operator=(Console const&);

	std::vector<std::string> m_command; //vector of user input

	FileParser m_fileparser; //handler for file io

	static bool m_continue; //determines whether console program should continue
};