#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "../utility/types.h"

class Compiler {
public:
	Compiler() {}
	~Compiler() {}

	Compiler(std::vector<std::string> contents) : m_contents(contents) {
		m_umap_rfunctions.insert({ "syscall", 0x0 });
		m_umap_rfunctions.insert({ "add", 0x2 });
		m_umap_rfunctions.insert({ "fadd", 0x3 });
		m_umap_rfunctions.insert({ "fsub", 0x4 });
		m_umap_rfunctions.insert({ "fmul", 0x5 });
		
		m_umap_ifunctions3param.insert({ "addi", 0xA });
		m_umap_ifunctions3param.insert({ "subi", 0xB });
		m_umap_ifunctions2param.insert({ "li", 0xC });
		m_umap_ifunctions3param.insert({ "lw", 0xD });
		m_umap_ifunctions2param.insert({ "la", 0xE });
		m_umap_ifunctions3param.insert({ "lb", 0xF });
		m_umap_ifunctions3param.insert({ "ld", 0x10 });
		m_umap_ifunctions3param.insert({ "sd", 0x11 });
		
		m_umap_jfunctions.insert({ "b", 0x1E });
		m_umap_ifunctions3param.insert({ "bge", 0x1C });
		m_umap_ifunctions2param.insert({ "beqz", 0x1B });
		m_umap_ifunctions3param.insert({ "bne", 0x1D });
		m_umap_jfunctions.insert({ "nop", 0x1F });
	}

	void compile() {
		findData();
		findInstructions();
		moveToMemory();
	}

private:
	//determine contents
	void findData();
	void findInstructions();
	const std::vector<std::string> findInstructionAndOperand(const std::string& s) const;

	//memory modifiers
	void moveToMemory();

	//per segment, by file parser
	void storeData(const std::vector<std::string>& values); //namely used by fileparser
	void storeInstruction(std::vector<std::string>& values); //namely used by fileparser
	//store specific instruction types
	void storeInstructionHelper(const std::string& type, const instruction_t& instr);

	std::unordered_map<std::string, int> m_umap_rfunctions;
	std::unordered_map<std::string, int> m_umap_ifunctions2param;
	std::unordered_map<std::string, int> m_umap_ifunctions3param;
	std::unordered_map<std::string, int> m_umap_jfunctions;
	std::unordered_map<std::string, int> m_umap_address;

	std::vector<std::string> m_contents;
	std::vector<std::string> m_data; // will be [variable][type][datum]
	std::vector<std::string> m_instructions; // will be [instruction]<optional>[ma_"memory address"] ex: [push][ma_X] 
};