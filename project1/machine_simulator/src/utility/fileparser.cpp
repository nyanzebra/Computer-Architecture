#include "fileparser.h"

#include "../memory/memory.h"

void FileParser::readFile() {
	if (m_filename.size() <= 0) {
		return;
	}

	m_filename = m_directory + m_filename;
	std::ifstream input(m_filename, std::ifstream::in);

	for (std::string line; getline(input, line);) {
		m_contents.push_back(line);
	}

	findData();
	findInstructions();
	moveToMemory();

	input.close();
}

void FileParser::readFile(const std::string& filename) {
	if (filename.size() <= 0) {
		return;
	}

	m_filename = m_directory + filename;

	std::ifstream input(m_directory + filename, std::ifstream::in);

	for (std::string line; getline(input, line);) {
		m_contents.push_back(line);
	}

	findData();
	findInstructions();
	moveToMemory();

	input.close();
}

void FileParser::printContents() const {
	for (std::string s : m_contents) {
		std::cout << s << std::endl;
	}
}

void FileParser::findData() {
	bool read = false;
	for (std::string s : m_contents) {
		if (read && s.find(":")) { //push back variable, type, datum
			std::string temp = s.substr(0,s.find(":"));
			m_data.push_back(temp);//get variable

			temp = s.substr(s.find(".")); //this is type and datum
			m_data.push_back(temp.substr(0,temp.find(" "))); //this is type

			temp = temp.substr(temp.find(" ") + 1);
			m_data.push_back(temp);//this is the datum
		}
		if (s == ".data") {
			read = true;
		}
		if (s == ".text") {
			read = false;
		}
	}
}

void FileParser::findInstructions() {
	bool read = false;

	for (std::string s : m_contents) {	
		if (read && s.find(":") != std::string::npos) { //this gives instruction address: main: , sub:
			std::string temp = s.substr(0, s.find("#")); //may need to check for comments first?
			//m_instructions.push_back(s);
		}
		if (read && m_instructions.size() >= 0 && s.find(":") == std::string::npos && s != ".data") {
			std::string temp = s.substr(0, s.find("#"));
			std::vector<std::string> v = findInstructionAndOperand(temp);
			for (std::string s : v) {
				m_instructions.push_back(s); //push back the instruction and operand if there is one
			}
		}
		if (s == ".text") {
			read = true;
		}
		if (s == ".data") {
			read = false;
		}
	}
}

const std::vector<std::string> FileParser::findInstructionAndOperand(const std::string& s) const {
	std::vector<std::string> temp;
	std::string value;

	for (char c : s) {
		if (c != ' ' && c != '\t') {
			value += c;
		}
		if (value.size() > 0 && c == ' ') {
			temp.push_back(value);
			value = "";
		}
	}

	if (value.size() > 0) {
		temp.push_back(value);
	}

	return temp;
}

void FileParser::moveToMemory() {
	bool is_data = false;
	bool is_instruction = false;

	for (std::string s : m_contents) {
		if (s.find(".text")) {
			is_instruction = true;
		} else if (s.find(".data")) {
			is_data = true;
		} 
		if (is_data) {
			Memory::storeData(m_data);
			m_data.clear();
		}
		if (is_instruction) {
			Memory::storeInstruction(m_instructions);
			m_instructions.clear();
		}
	}
}