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
#include "../logic/logic.h"

class Memory { 
public:
	static mem_t m_stack_counter; // points to top of stack
	static mem_t m_instruction_counter; //points to last instruction address

	static void storeData(const mem_t& mem_addr, const data_t& data); //store data into memory
	static void storeInstruction(const mem_t& mem_addr, const instruction_t& data); // store instruction into memory
	static void storeFData(const mem_t&, const float& data);

	static data_t loadData(const mem_t& location); //load exclusively data
	static data_t loadStack(const mem_t& location); //load exclusively data
	static float loadFData(const mem_t& location);

	static instruction_t loadInstruction(const mem_t& location); //load exclusively instructions

	static void clear() { m_dmemory.clear(); m_fmemory.clear(); m_imemory.clear(); m_instruction_counter = 0; } // delete everything

private:
	static std::vector<data_t> m_dmemory; //memory data structure
	static std::vector<float> m_fmemory; //float memory
	static std::vector<instruction_t> m_imemory; //instruction memory
};
