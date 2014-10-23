#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../utility/types.h"

// dir: /home/robert/Desktop/CA_PROJECT1/assembly_code

//TODO:
//need to get labels main,loop, etc
//create formatted instructions
//hashing labels
//need a .space thingy
//change branch stuff

class FileParser {
public:
	FileParser() { 
		m_umap_ifunctions2param.insert({ "la", 0xE });
		m_umap_ifunctions2param.insert({ "li", 0xC });
		m_umap_ifunctions3param.insert({ "lb", 0xF });
		m_umap_ifunctions3param.insert({ "lw", 0xD });
		m_umap_ifunctions3param.insert({ "addi", 0xA });
		m_umap_ifunctions3param.insert({ "subi", 0xB });
		m_umap_rfunctions.insert({ "syscall", 0x0 });
		m_umap_jfunctions.insert({ "b", 0x1E });
		m_umap_ifunctions3param.insert({ "bge", 0x1C });
		m_umap_ifunctions2param.insert({ "beqz", 0x1B });
		m_umap_ifunctions3param.insert({ "bne", 0x1D });
		m_umap_jfunctions.insert({ "nop", 0x1F });
		m_umap_rfunctions.insert({ "add", 0x2 });
	};

	//store specific instruction types
	void storeInstructionHelper(const std::string& type, const instruction_t& instr);

	//file handlers
	void setDirectory(const std::string& dir) { m_directory = dir; }
	void readFile(const std::string& filename);
	void printContents() const;

	//has data
	const bool& isEmpty() { return (m_contents.size() > 0) ? false : true; } 

	//accessors
	const std::string& getFilename() { return m_filename; }
	
private:
	//determine extension
	std::string getFileExtension(const std::string& filename) {

		if (filename.find_last_of(".") != std::string::npos) {
			return filename.substr(filename.find_last_of(".") + 1);
		}

		return "";
	}

	//determine contents
	void findData();
	void findInstructions();
	const std::vector<std::string> findInstructionAndOperand(const std::string& s) const;

	//memory modifiers
	void moveToMemory();

	//per segment, by file parser
	void storeData(const std::vector<std::string>& values); //namely used by fileparser
	void storeInstruction(std::vector<std::string>& values); //namely used by fileparser

	std::string m_filename; // current file
	std::string m_directory; //current dir

	std::unordered_map<std::string, int> m_umap_rfunctions;
	std::unordered_map<std::string, int> m_umap_ifunctions2param;
	std::unordered_map<std::string, int> m_umap_ifunctions3param;
	std::unordered_map<std::string, int> m_umap_jfunctions;
	std::unordered_map<std::string, int> m_umap_address;
	std::vector<std::string> m_contents; // will be entire file each [] is a line of the file
	std::vector<std::string> m_data; // will be [variable][type][datum]
	std::vector<std::string> m_instructions; // will be [instruction]<optional>[ma_"memory address"] ex: [push][ma_X] 
};