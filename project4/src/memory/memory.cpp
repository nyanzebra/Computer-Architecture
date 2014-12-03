#include "memory.h"

//initialize containers
std::vector<data_t> Memory::m_dmemory(MAX_SEGMENT_DATA + MAX_SEGMENT_INSTRUCTION);
std::vector<float> Memory::m_fmemory(MAX_SEGMENT_FLOAT);
std::vector<instruction_t> Memory::m_imemory(MAX_SEGMENT_INSTRUCTION);
//initialize counters
unsigned int Memory::m_instruction_counter = 0;

data_t Memory::loadData(const mem_t& addr) {
	if (addr < MIN_SEGMENT_DATA || addr > MAX_SEGMENT_DATA) { // bad address
		return NULL;
	}
	return m_dmemory[addr]; // return data at address addr
}

float Memory::loadFData(const mem_t& addr) {
	if (addr < MIN_SEGMENT_DATA || addr > MAX_SEGMENT_DATA) { // bad address
		return NULL;
	}
	return m_fmemory[addr]; // return data at address addr
}

instruction_t Memory::loadInstruction(const mem_t& addr) {
	if (addr < MIN_SEGMENT_INSTRUCTION || addr > MAX_SEGMENT_INSTRUCTION) { // bad address
		return instruction_t();
	}
	return m_imemory[addr];
}

void Memory::storeData(const mem_t& addr, const data_t& data) {
	if (m_dmemory.size() == 0) { // a check to see if memory has been initialized
		m_dmemory = std::vector<data_t>(MAX_SEGMENT_DATA + MAX_SEGMENT_INSTRUCTION);
	}
	if (addr < MIN_SEGMENT_DATA || addr > MAX_SEGMENT_DATA) { // bad address
		return; //nothing happens
	} else {
		m_dmemory[addr] = data;
	}
}

void Memory::storeInstruction(const mem_t& addr, const instruction_t& instruction) {
	if (addr < MIN_SEGMENT_INSTRUCTION || addr > MAX_SEGMENT_INSTRUCTION) { // bad address
		return; // nothing happens...
	}
	if (m_imemory.size() == 0) {
		m_imemory = std::vector<instruction_t>(MAX_SEGMENT_INSTRUCTION);
	}
	m_imemory[addr] = instruction;
}

void Memory::storeFData(const mem_t& addr, const float& data) {
	if (m_fmemory.size() == 0) { // a check to see if memory has been initialized
		m_fmemory = std::vector<float>(MAX_SEGMENT_FLOAT);
	}
	if (addr < MIN_SEGMENT_FLOAT || addr > MAX_SEGMENT_FLOAT) { // bad address
		return; //nothing happens
	} else {
		m_fmemory[addr] = data;
	}
}