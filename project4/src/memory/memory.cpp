#include "memory.h"

//initialize containers
std::vector<data_t> Memory::m_memory(MAX_SEGMENT_DATA + MAX_SEGMENT_INSTRUCTION + MAX_SEGMENT_STACK);

//initialize counters
unsigned int Memory::m_instruction_counter = 0;
unsigned int Memory::m_stack_counter = MIN_SEGMENT_STACK;

data_t Memory::loadData(const mem_t& addr) {
	if (addr < MIN_SEGMENT_DATA || addr > MAX_SEGMENT_DATA) { // bad address
		return NULL;
	}
	return m_memory[addr]; // return data at address addr
}

data_t Memory::loadStack(const mem_t& addr) {
	if (addr < MIN_SEGMENT_STACK || addr > MAX_SEGMENT_STACK) {
		return NULL;
	}
	return m_memory[addr];
}

instruction_t Memory::loadInstruction(const mem_t& addr) {
	if (addr < MIN_SEGMENT_INSTRUCTION || addr > MAX_SEGMENT_INSTRUCTION) { // bad address
		return NULL;
	}
	return m_memory[addr];
}

void Memory::erase(const mem_t& begin, const mem_t& end) {
	for (mem_t i = begin; i < end; ++i) { //insert null in range of begin->end
		m_memory[i] = NULL;
	}
}

void Memory::storeData(const mem_t& addr, const data_t& data) {
	if (m_memory.size() == 0) { // a check to see if memory has been initialized
		m_memory = std::vector<data_t>(MAX_SEGMENT_DATA + MAX_SEGMENT_INSTRUCTION + MAX_SEGMENT_STACK);
	}
	if (addr < MIN_SEGMENT_DATA || addr > MAX_SEGMENT_DATA) { // bad address
		return; //nothing happens
	} else {
		m_memory[addr] = data;
	}
}

void Memory::storeInstruction(const mem_t& addr, const instruction_t& instruction) {
	if (addr < MIN_SEGMENT_INSTRUCTION || addr > MAX_SEGMENT_INSTRUCTION) { // bad address
		return; // nothing happens...
	}
	if (m_memory.size() == 0) {
		m_memory = std::vector<data_t>(MAX_SEGMENT_DATA + MAX_SEGMENT_INSTRUCTION + MAX_SEGMENT_STACK);
	}
	m_memory[addr] = instruction;
}