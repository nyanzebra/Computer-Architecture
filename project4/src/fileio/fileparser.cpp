#include <fstream>
#include <iostream>

#include "../logic/logic.h"
#include "../memory/memory.h"
#include "fileparser.h"
#include "../machine/generalpurposeregistermachine.h"

void FileParser::readFile(const std::string& filename) {
	m_contents.clear();
	if (filename.size() <= 0) { //obviously
		return;
	}

	m_filename = m_directory + filename;//set path

	std::ifstream input(m_directory + filename, std::ifstream::in);

	for (std::string line; getline(input, line);) {
		m_contents.push_back(line);
	}

	input.close(); //close file
}

void FileParser::printContents() const { //print file contents
	for (std::string s : m_contents) {
		std::cout << s << std::endl;
	}
}
