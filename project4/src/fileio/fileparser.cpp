#include <fstream>
#include <iostream>

#include "../logic/logic.h"
#include "../memory/memory.h"
#include "fileparser.h"
#include "../machine/generalpurposeregistermachine.h"

std::string FileParser::m_filename = "";

std::vector<std::string>& FileParser::readFile(const std::string& filename) {
	m_contents.clear();
	m_filename = filename;

	std::ifstream input(m_directory + filename, std::ifstream::in);

	for (std::string line; getline(input, line);) {
		m_contents.push_back(line);
	}

	input.close(); //close file
	return m_contents;
}

void FileParser::printContents() const { //print file contents
	for (std::string s : m_contents) {
		std::cout << s << std::endl;
	}
}
