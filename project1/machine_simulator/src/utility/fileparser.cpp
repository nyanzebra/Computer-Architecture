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
		if (s.find(".data")) {
			read = true;
		}
		if (s.find(".text")) {
			read = false;
		}
		if (read && s.find(":")) { //push back variable, type, datum
			std::string temp = s.substr(0,s.find(":"));
			m_data.push_back(temp);//get variable

			temp = s.substr(s.find(".")); //this is type and datum
			m_data.push_back(temp.substr(0,temp.find(" "))); //this is type

			temp = temp.substr(temp.find(" ")).replace(0, temp.find_last_of(" "), "");
			m_data.push_back(temp);//this is the datum
		}
	}
}

void FileParser::findInstructions() {
	bool read = false;
	for (std::string s : m_contents) {
		if (s.find(".text")) {
			read = true;
		}
		if (s.find(".data")) {
			read = false;
		}
		if (read && s.find(":")) { //this gives instruction address: main: , sub:
			std::string temp = s.substr(0, s.find("#")); //may need to check for comments first?
			m_instructions.push_back(s);
		}
		if (read && m_instructions.size() > 0) {
			std::string temp = s.substr(0, s.find("#"));
			for (std::string s : findInstructionAndOperand(temp)) {
				m_instructions.push_back(s); //push back the instruction and operand if there is one
			}
		}
	}
}

const std::vector<std::string>& FileParser::findInstructionAndOperand(const std::string& s) const {
	std::vector<std::string> temp;
	std::string value;
	int i = 0;

	for (char c : s) {
		if (c != ' ') {
			value += c;
		}
		if (value.size() > 0 && c == ' ') {
			temp.push_back(value);
			value = "";
			++i;
		}
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