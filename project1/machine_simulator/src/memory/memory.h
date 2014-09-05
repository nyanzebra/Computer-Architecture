#pragma once

#include <vector>
#include <string>
#include <list>

#include "../utility/types.h"

#define max_data_size 5000
#define max_instruction_size 5000
#define max_address_size 1500

//global memory class
class Memory { //TODO need a way to move whole chunks of memory over x blocks to store other data so it is not overwritten or have it point to multiple areas
public:

	//store data wherever it can
	static void store(const byte data); // store data at end of memory of given size
	static void store(const halfword data); // store data at end of memory of given size
	static void store(const word data); // store data at end of memory of given size
	//store data at certain location can overwrite
	static void store(const std::list<byte>& data); //store temp data 
	static void store(const memory_address& mem_addr, const std::list<byte>& data); //store variable length 
	static void storeData(const byte* mem_addr, const std::list<byte>& data); //store variable length data
	//store one memory data into another location
	static void store(const int& begin, const int& end, const std::list<byte>& data); // store memory at range begin->end and erase whatever was there before
	static void store(const byte* mem_addr_0, const byte* mem_addr_1); //store memory at range of two addresses and erase what was there before
	//load data from address
	static std::list<byte> load(memory_address& mem_addr); // load from an address
	static std::list<byte> loadData(const byte* location); //load exclusively data
	static std::list<byte> loadData(const memory_address& location); //load exclusively data
	static std::list<byte> loadInstruction(int& location); //load exclusively instructions
	//clear all memory
	static void clear() { m_memory_data.clear(); m_memory_instruction.clear(); m_addresses.clear(); } // delete everything
	//erase a segment
	static void erase(const int& begin, const int& end); //delets memory at range of begin->end

	//size
	static unsigned int& getMemoryInstructionSize() { return m_instruction_counter; } //get size of bytes for all instructions
	static unsigned int& getMemoryDataSize() { return m_data_counter; } //get size of bytes for all data

	//temporary data
	static void createTemporaryDataArea();

	//per segment
	static void storeData(const std::vector<std::string>& values);
	static void storeInstruction(const std::vector<std::string>& values);

private:
	//segmented memory, data, instruction, comments?
	static std::vector<byte> m_memory_data;
	static std::vector<byte> m_memory_instruction;
	static std::vector<memory_address> m_addresses;

	//pointers
	static unsigned int m_data_counter;
	static unsigned int m_instruction_counter;
	static unsigned int m_address_counter;
};