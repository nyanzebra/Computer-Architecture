#include <fstream>
#include <iostream>

#include "logic.h"
#include "memory.h"
#include "fileparser.h"

void FileParser::readFile() {
	m_contents.clear();
	
	if (m_filename.size() <= 0) { //obviously
		return;
	}

	m_filename = m_directory + m_filename; //set path
	std::ifstream input(m_filename, std::ifstream::in);

	for (std::string line; getline(input, line);) {
		m_contents.push_back(line);
	}

	findData(); //get all the data
	findInstructions(); //get all the instructions
	moveToMemory(); //move them to memory

	input.close(); //close file
}

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

	findData(); //get all the data
	findInstructions(); //get all the instructions
	moveToMemory(); //move them to memory

	input.close(); //close file
}

void FileParser::printContents() const { //print file contents
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
		if (c != ' ' && c != '\t') { //basically a tokenizer of sorts
			value += c;
		}
		if (value.size() > 0 && (c == ' ' || c == '\t')) { //get each piece of an instruction
			temp.push_back(value);
			value = "";
		}
	}

	if (value.size() > 0) { //if just one piece catch it
		temp.push_back(value);
	}

	return temp;
}

void FileParser::moveToMemory() {
	bool is_data = false;
	bool is_instruction = false;

	Memory::clear(); // clear memory

	storeData(m_data); //move to data
	m_data.clear(); //delete the data collection

	storeInstruction(m_instructions);//move to instructions
	m_instructions.clear(); //delete the instruction collection
}

void FileParser::storeData(const std::vector<std::string>& values) {

	int d_offset = MIN_SEGMENT_DATA; //begin of data segment
	for (auto it = values.begin(); it != values.end(); ++it) { //for all the data place them in memory correctly
		 //put in all aliases and size(induced by locations) in memory address container
			m_umap_address.insert({ *it, d_offset });
			++it;
		 //get type
		if (*it == ".byte") {
			++it;
			Memory::storeData(d_offset++, (int)(it->operator[](0))); //store a byte and increment offset
		}
		else if (*it == ".halfword") {
			++it;
			Memory::storeData(d_offset++, (int)(it->operator[](0))); //store a halfword and increment offset
		}
		else if (*it == ".word") {
			++it;
			Memory::storeData(d_offset++, (int)(it->operator[](0))); //store a word and increment offset
		}
		else if (*it == ".asciiz") {
			++it;
			if (*it != "\"\\n\"") { //check if new line character
				std::string s = *it; // want to remove '"'
				Logic::m_hash_strings->insert({ 0x80000000 | d_offset, s.substr(1, s.size() - 2) }); //goal is to hash all ascii strings
				Memory::storeData(d_offset++, 0x80000000 | d_offset); //then retrieve them by unhashing...
			} else {
				Memory::storeData(d_offset++, 10); //store a byte and increment offset
			}
		}
	}
}

void FileParser::storeInstruction(const std::vector<std::string>& instructions) {

	Memory::machine type; // this is used as indicator to determine what machine instructions to use
	int i_offset = MIN_SEGMENT_INSTRUCTION; // begin of instruction segment

	for (auto it = instructions.begin(); it != instructions.end(); ++it) {
		if (*it == "push") {
			type = Memory::stackmachine; // set machine type so proper instructions are emplaced
			++it; // get alias
			int addr = m_umap_address.find(*it)->second; // get memory address for that alias
			instruction_t instruction = addr | 0x01000000; // or with arbitray hex to get opcode added to the instruction
			Memory::storeInstruction(i_offset, instruction);
			i_offset++;
		} else if (*it == "pop") {
			++it; // get alias
			int addr = m_umap_address.find(*it)->second; // get memory address for that alias
			instruction_t instruction = addr | 0x02000000; // or with arbitray hex to get opcode added to the instruction
			Memory::storeInstruction(i_offset, instruction);
			i_offset++;
		} else if (*it == "stor") {
			++it; // get alias
			int addr = m_umap_address.find(*it)->second; // get memory address for that alias
			instruction_t instruction = addr | 0x02000000; // or with arbitray hex to get opcode added to the instruction
			Memory::storeInstruction(i_offset, instruction);
			i_offset++;
		} else if (*it == "load") {
			type = Memory::accummachine;// set machine type so proper instructions are emplaced
			++it; // get alias
			int addr = m_umap_address.find(*it)->second; // get memory address for that alias
			instruction_t instruction = addr | 0x01000000; // or with arbitray hex to get opcode added to the instruction
			Memory::storeInstruction(i_offset, instruction);
			i_offset++;
		} else if (*it == "add") {
			if (type != Memory::accummachine){
				Memory::storeInstruction(i_offset, 0x03000000);
			} else {
				++it; // get alias
				int addr = m_umap_address.find(*it)->second; // get memory address for that alias
				instruction_t instruction = addr | 0x03000000; // or with arbitray hex to get opcode added to the instruction
				Memory::storeInstruction(i_offset, instruction);
			}
			i_offset++;
		} else if (*it == "mult") {
			if (type != Memory::accummachine){
				Memory::storeInstruction(i_offset, 0x04000000);
			} else {
				++it; // get alias
				int addr = m_umap_address.find(*it)->second; // get memory address for that alias
				instruction_t instruction = addr | 0x04000000; // or with arbitray hex to get opcode added to the instruction
				Memory::storeInstruction(i_offset, instruction);
			}
			i_offset++;
		} else if (*it == "prnt") {
			Memory::storeInstruction(i_offset, 0x05000000);
			i_offset++;
		} else if (*it == "end") {
			Memory::storeInstruction(i_offset, 0x06000000);
			i_offset++;
		}
	}

	//set instruction counter to offset
	Memory::m_instruction_counter = i_offset;
	// now we can delete our map!
	m_umap_address.clear();
}
