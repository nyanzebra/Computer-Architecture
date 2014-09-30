#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// dir: /home/robert/Desktop/CA_PROJECT1/assembly_code

class FileParser {
public:
	//constructors
	FileParser() {}
	~FileParser() {}
	
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
	void storeInstruction(const std::vector<std::string>& values); //namely used by fileparser

	std::string m_filename; // current file
	std::string m_directory; //current dir

	std::unordered_map<std::string, int> m_umap_address;
	std::vector<std::string> m_contents; // will be entire file each [] is a line of the file
	std::vector<std::string> m_data; // will be [variable][type][datum]
	std::vector<std::string> m_instructions; // will be [instruction]<optional>[ma_"memory address"] ex: [push][ma_X] 
};