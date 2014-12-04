#pragma once

#include <string>
#include <vector>

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

	//file handlers
	void setDirectory(const std::string& dir) { m_directory = dir; }
	std::vector<std::string>& readFile(const std::string& filename);
	void printContents() const;

	//has data
	const bool& isEmpty() { return (m_contents.size() > 0) ? false : true; } 

	//accessors
	static std::string& getFilename() { return m_filename; }
	
private:
	//determine extension
	std::string getFileExtension(const std::string& filename) {
		if (filename.find_last_of(".") != std::string::npos) {
			return filename.substr(filename.find_last_of(".") + 1);
		}
		return "";
	}

	static std::string m_filename; // current file
	std::string m_directory; //current dir
	std::vector<std::string> m_contents; // will be entire file each [] is a line of the file
};