#pragma once

//robert baldwin
//this is the memory class
//it is global and can be used wherever in the code given proper include
//it is capable of storing instructions and data, loading instructions and data,
//keeping track of memory addresses
//writing over memory
//clearing memory
//please follow same format throughout!

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "../utility/types.h"
#include "../utility/lambdas.h"
#include "../logic/logic.h"

//some size definitions.. we will need to add some handlers for this
//as we do not want our containers to exceed this value
//this may mean switching to a queue over a vector
#define max_data_size 5000
#define max_instruction_size 5000
#define max_address_size 1500

class Memory { 
public:
	enum machine {
		stackmachine,
		accummachine,
	};
	//store data at certain location can overwrite
	static void storeData(const memoryAddress_s& mem_addr, const std::list<byte_t>& data); //store variable length 
	static void storeData(const byte_t* mem_addr, const std::list<byte_t>& data); //store variable length data
	//store one memory data into another location
	static void store(const int& begin, const int& end, const std::list<byte_t>& data); // store memory at range begin->end and erase whatever was there before
	//load data from address
	static std::list<byte_t> loadData(const byte_t* location); //load exclusively data
	static std::list<byte_t> loadData(const memoryAddress_s& location); //load exclusively data
	static std::list<byte_t> loadInstruction(unsigned int& location); //load exclusively instructions

	//clear all memory
	static void clear() { m_memory_data.clear();} // delete everything
	//erase a segment
	static void erase(const int& begin, const int& end); //delets memory at range of begin->end

	static void copy() { *m_data_copy = m_memory_data; };
	static void restore() {
		m_memory_data = *m_data_copy; 
		//m_data_counter=0; 
		//m_instruction_counter = 0;
		//m_address_counter = 0; 
		if (m_memory_instruction.size() == 0) {
			std::cout << "here is the error";
			//m_memory_instruction = L_makebyte_tVector(max_instruction_size);
		}
}	
	static void clearPrevious() { m_memory_instruction.clear(); m_memory_data.clear(); m_data_counter = 0; m_instruction_counter=0; m_address_counter=0;}
	//size
	static unsigned int& getMemoryInstructionSize() { return m_instruction_counter; } //get size of byte_ts for all instructions
	static unsigned int& getMemoryDataSize() { return m_data_counter; } //get size of byte_ts for all data

	//per segment, by file parser
	static void storeData(const std::vector<std::string>& values); //namely used by fileparser
	static void storeInstruction(const std::vector<std::string>& values); //namely used by fileparser

private:
	//segmented memory, data, instruction
	static std::vector<byte_t>* m_data_copy;
	static std::vector<byte_t> m_memory_data;
	static std::vector<byte_t> m_memory_instruction;
	static std::vector<memoryAddress_s> m_addresses;

	//pointers
	static unsigned int m_data_counter;
	static unsigned int m_instruction_counter;
	static unsigned int m_address_counter;
};
