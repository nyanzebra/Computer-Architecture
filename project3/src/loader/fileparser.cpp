#include <fstream>
#include <iostream>
#include <algorithm>

#include "../logic/logic.h"
#include "../memory/memory.h"
#include "fileparser.h"
#include "../machine/generalpurposeregistermachine.h"

//bad characters
bool isBadCharacter(char c) {
	switch (c) {
	case '\t':
		return true;
	default:
		return false;
	}
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
			std::string temp = s.substr(0, s.find(":"));
			m_data.push_back(temp);//get variable

			temp = s.substr(s.find(".")); //this is type and datum
			m_data.push_back(temp.substr(0, temp.find(" "))); //this is type

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
			std::string label = s.substr(0, s.find("#")); //may need to check for comments first?
			m_instructions.push_back(label); //use map??
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
		if (c != ' ' && c != '\t' && c != ',' && c != '$') { //basically a tokenizer of sorts
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
	Base_Machine::clear();

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
		} else if (*it == ".halfword") {
			++it;
			Memory::storeData(d_offset++, (int)(it->operator[](0))); //store a halfword and increment offset
		} else if (*it == ".word") {
			++it;
			Memory::storeData(d_offset++, (int)(it->operator[](0))); //store a word and increment offset
		} else if (*it == ".asciiz") {
			++it;
			std::string s = *it; // want to remove '"'
			if (it->find("\\n") != std::string::npos) {
				s.replace(s.find("\\n"), 2, "\n");
			}
			Logic::m_hash_strings->insert({ 0x80000000 | d_offset, s.substr(1, s.size() - 2) }); //goal is to hash all ascii strings
			Memory::storeData(d_offset++, 0x80000000 | d_offset); //then retrieve them by unhashing...
		} else if (*it == ".space") {
			++it;
			d_offset += std::stoi(*it); // allocate free space
		}
	}
}

void FileParser::storeInstruction(std::vector<std::string>& instructions) {

	Memory::machine type; // this is used as indicator to determine what machine instructions to use
	int instruction_offset = MIN_SEGMENT_INSTRUCTION; // begin of instruction segment
	std::unordered_map<std::string, int> options =
	{
		{ "la", 14 },
		{ "li", 12 },
		{ "lb", 15 },
		{ "lw", 13 },
		{ "addi", 10 },
		{ "subi", 11 },
		{ "syscall", 0 },
		{ "add", 2 },
		{ "nop", 31 },
		{ "b", 30 },
		{ "bge", 28 },
		{ "beqz", 27 },
		{ "bne", 29 }
	};
	//sub: label
	//replace sub: with instruction_offset
	//[label][][][][b][label][]
	//offset -------->offset
	//loop through and replace label with offset
	int counter = 0;
	for (int i = 0; i < instructions.size(); ++i) {
		if (options.find(instructions[i]) != options.end()) {
			counter++;
		}

		if (instructions[i].find(":") != std::string::npos) {
			instructions[i].erase(std::remove_if(instructions[i].begin(), instructions[i].end(), &isBadCharacter), instructions[i].end());

			for (int j = 0; j < instructions.size(); ++j) {
				if (instructions[i].substr(0, instructions[i].size() - 1) == instructions[j]) {
					instructions[j] = std::to_string(counter);
				}
			}
			instructions[i] = "0";
		}
	}

	for (auto it = instructions.begin(); it != instructions.end(); ++it) { //li $5,45
		if (m_umap_ifunctions2param.find(*it) != m_umap_ifunctions2param.end()) {
			instruction_t instr = m_umap_ifunctions2param.find(*it)->second << 26 | std::stoi(*(++it)) << 16; //concatenates instruction params			
			if (m_umap_address.find(*(++it)) != m_umap_address.end()){ //add on hash value if it is string otherwise or whatever
				instr |= m_umap_address.find(*it)->second;
			} else {
				instr |= std::stoi(*(it));
			}
			storeInstructionHelper(*it, instr);
		} else if (m_umap_ifunctions3param.find(*it) != m_umap_ifunctions3param.end()) {
			instruction_t instr = m_umap_ifunctions3param.find(*it)->second << 26 | std::stoi(*(++it)) << 16 | std::stoi(*(++it)) << 21; //concatenates instruction params
			if (m_umap_address.find(*(++it)) != m_umap_address.end()){ //add on hash value if it is string otherwise or whatever
				instr |= m_umap_address.find(*it)->second;
			} else {
				instr |= std::stoi(*(it));
			}
			storeInstructionHelper(*it, instr);
		} else if (m_umap_rfunctions.find(*it) != m_umap_rfunctions.end()) {
			if (*it == "syscall") {
				storeInstructionHelper(*it, m_umap_rfunctions.find(*it)->second << 26);
			} else {
				instruction_t instr = m_umap_rfunctions.find(*it)->second | std::stoi(*(++it)) << 11 | std::stoi(*(++it)) << 21 | std::stoi(*(++it)) << 16 | std::stoi(*(++it)) << 6;
				storeInstructionHelper(*it, instr);
			}
		} else if (m_umap_jfunctions.find(*it) != m_umap_jfunctions.end()) {
			if (*it == "nop") {
				Base_Machine::incrementNopCount();
				instruction_t instr = m_umap_jfunctions.find(*it)->second << 26;
				storeInstructionHelper(*it, instr);
			} else {
				instruction_t instr = m_umap_jfunctions.find(*it)->second << 26 | std::stoi(*(++it));
				storeInstructionHelper(*it, instr);
			}
		}
	}
	// now we can delete our map!
	m_umap_address.clear();
}

void FileParser::storeInstructionHelper(const std::string& type, const instruction_t& instruction) {
	Memory::storeInstruction(Memory::m_instruction_counter, instruction);
	Memory::m_instruction_counter++;
}