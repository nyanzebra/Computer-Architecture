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
#include "types.h"
#include "lambdas.h"
#include "logic.h"

class Memory { 
public:
	enum machine {
		stackmachine,
		accummachine,
	};

	static mem_t m_stack_counter; // points to top of stack
	static mem_t m_instruction_counter; //points to last instruction address

	static void storeData(const mem_t& mem_addr, const data_t& data); //store data into memory
	static void storeInstruction(const mem_t& mem_addr, const instruction_t& data); // store instruction into memory
	static data_t loadData(const mem_t& location); //load exclusively data
	static data_t loadStack(const mem_t& location); //load exclusively data
	static instruction_t loadInstruction(const mem_t& location); //load exclusively instructions

	static void clear() { m_memory.clear(); } // delete everything
	static void erase(const mem_t& begin, const mem_t& end); //delets memory at range of begin->end

	static const data_t topStack() { return m_memory[m_stack_counter - 1]; } //get back of stack
	static void popStack() { //just remove the top of stack
		m_memory[m_stack_counter - 1] = NULL;
		m_stack_counter--;
	}
	static void popStack(const mem_t& addr) { // put data from stack into addr remove top of stack
		m_memory[addr] = loadStack(m_stack_counter - 1);
		m_memory[m_stack_counter] = NULL;
		m_stack_counter--;
	} 
	static void pushStackAddr(const mem_t& addr) {// push data onto stack
		m_memory[m_stack_counter] = loadData(addr);
		m_stack_counter++;
	} 
	static void pushStackData(const data_t& data) {// push data onto stack
		m_memory[m_stack_counter] = data;
		m_stack_counter++;
	}

private:
	static std::vector<data_t> m_memory; //memory data structure
};
