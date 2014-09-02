#pragma once

#include <vector>
#include <string>

#include "../utility/heapgeneric.h"
#include "../utility/types.h"

class Memory {
public:
	Memory() {}
	~Memory();

	//init
	static void init();

	//modifiers for the per segments
	//store data wherever it can
	static void store(const byte data);
	static void store(const halfword data);
	static void store(const word data);
	//store data at certain location can overwrite
	static void store(const memory_address& mem_addr, const byte data);
	static void store(const memory_address& mem_addr, const halfword data);
	static void store(const memory_address& mem_addr, const word data);
	//load data from address
	static void* load(const memory_address& mem_addr);
	//clear all memory
	static void clear();
	//erase a segment
	static void erase(const memory_address& begin, const memory_address& end);

	//per segment
	static void storeData(const std::vector<std::string>& values);
	static void storeInstruction(const std::vector<std::string>& values);
	static void storeComments(const std::vector<std::string>& values);

private:
	//segmented memory, data, instruction, comments?
	static Heap_Generic<byte>* m_memory_data;
	static Heap_Generic<byte>* m_memory_instruction;
	static Heap_Generic<byte>* m_memory_comments;
	static std::vector<memory_address>* m_addresses;

	//pointers
	static unsigned int* m_data_pointer;
	static unsigned int* m_instruction_pointer;
};