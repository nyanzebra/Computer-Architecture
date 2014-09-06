#pragma once

#ifndef PCH_H
#include "../pch.h"
#endif

// dir: /home/robert/Desktop/CA_PROJECT1/assembly_code

class FileParser {
public:
	//constructors
	FileParser() {}
	FileParser(const std::string& filename) : m_filename(filename) {}
	~FileParser() {}
	
	//file handlers
	void setDirectory(const std::string& dir) { m_directory = dir; }
	void readFile();
	void readFile(const std::string& filename);
	void printContents() const;

	//determine contents
	void findData();
	void findInstructions();
	const std::vector<std::string> findInstructionAndOperand(const std::string& s) const;

	//has data
	const bool&& isEmpty() { return (m_contents.size() > 0) ? false : true; } 

	//determine extension
	std::string getFileExtension(const std::string& filename) {

		if (filename.find_last_of(".") != std::string::npos) {
			return filename.substr(filename.find_last_of(".") + 1);
		}

		return "";
	}

	//accessors
	const std::string& getFilename() { return m_filename; }

	//memory modifiers
	void moveToMemory();
private:
	std::string m_filename;
	std::string m_directory;

	std::vector<std::string> m_contents; // will be entire file each [] is a line of the file
	std::vector<std::string> m_data; // will be [variable][type][datum]
	std::vector<std::string> m_instructions; // will be [instruction]<optional>[ma_"memory address"] ex: [push][ma_X] 
};