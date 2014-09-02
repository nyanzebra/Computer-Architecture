#include "memory.h"


//initialize static variables
unsigned int * Memory::m_data_pointer = nullptr;
unsigned int* Memory::m_instruction_pointer = nullptr;

Heap_Generic<byte>* Memory::m_memory_data = new Heap_Generic<byte>();
Heap_Generic<byte>* Memory::m_memory_comments = new Heap_Generic<byte>();
Heap_Generic<byte>* Memory::m_memory_instruction = new Heap_Generic<byte>();
std::vector<memory_address>* Memory::m_addresses = new std::vector<memory_address>();

void Memory::init() {
	*m_data_pointer = 0;
	*m_instruction_pointer = 0;
}

void Memory::storeData(const std::vector<std::string>& values) {
	//first we read the data from values
	//store any address, for instance x: .word 3 should store mem_address(int,x);
	//store values by distance according to type
	//store in datum
	//values format = [variable][type][datum]

	int counter = 0;// 3 options and need to handle it accordingly
	bool is_ascii = false;
	for (std::string s : values) {
		if (counter == 0) {
			memory_address mem;
			mem.address = *m_data_pointer;

			for (char c : s) {
				mem.value += c;
			}

			m_addresses->push_back(mem);
		} 
		if (counter == 1) {
			if (s.find("byte")) {
				m_memory_data->insert('?'); //this is the substitute for NULL, we need to put an unknown as the seperator 
				*m_data_pointer = m_memory_data->size(); //move data pointer along to top or back of vector
			} else if (s.find("halfword")) {
				m_memory_data->insert('?');
				m_memory_data->insert('?');
				*m_data_pointer = m_memory_data->size();
			} else if (s.find("word")) {
				m_memory_data->insert('?');
				m_memory_data->insert('?');
				m_memory_data->insert('?');
				m_memory_data->insert('?');
				*m_data_pointer = m_memory_data->size();
			} else if (s.find("asciiz")) {
				is_ascii = true;
			}
		}
		if (counter == 2 && !is_ascii) {
			m_memory_data->operator[](*m_data_pointer - 1) = s[0]; //insert char 
			counter = 0;
		}
		if (counter == 2 && is_ascii) {
			for (char c : s) {
				m_memory_data->insert(c);
				m_data_pointer++;
			}
			is_ascii = false;
		}
		counter++;
	}
}

void Memory::storeInstruction(const std::vector<std::string>& instructions) {
	//first we read the instructions from instructions
	//TODO: store the instruction pointer for instance main needs an address,sub needs an address
	//instructions format [instruction]<optional>[operand]
	//all instructions will be word size two chars for instruction, two chars for operand
	//for instance push x could be [p][u][o][x] which would read push operand x
	//if reading each as word we should probably have everything as word size?

	for (auto it = instructions.begin(); it != instructions.end(); ++it) {
		if (*it == "push") {
			m_memory_instruction->insert('p');
			m_memory_instruction->insert('u');
			m_memory_instruction->insert('o');
			++it;
			m_memory_instruction->insert(it->operator[](0));
			*m_instruction_pointer = m_memory_data->size(); //move isntruction pointer along to top or back of vector
		} else if (*it == "pop") {
			m_memory_instruction->insert('p');
			m_memory_instruction->insert('o');
			m_memory_instruction->insert('o');
			++it;
			m_memory_instruction->insert(it->operator[](0));
			*m_instruction_pointer = m_memory_data->size();
		} else if (*it == "add") {
			m_memory_instruction->insert('a');
			m_memory_instruction->insert('d');
			*m_instruction_pointer = m_memory_data->size();
		} else if (*it == "mult") {
			m_memory_instruction->insert('m');
			m_memory_instruction->insert('u');
			*m_instruction_pointer = m_memory_data->size();
		} else if (*it == "prnt") {
			m_memory_instruction->insert('p');
			m_memory_instruction->insert('r');
			*m_instruction_pointer = m_memory_data->size();
		} else if (*it == "end") {
			m_memory_instruction->insert('e');
			m_memory_instruction->insert('n');
			*m_instruction_pointer = m_memory_data->size();
		}
	}
}