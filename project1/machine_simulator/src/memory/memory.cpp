#include "memory.h"
#include "../utility/makeconstructs.h"

//initialize containers
std::vector<byte> Memory::m_memory_data = makeVector<byte>(max_data_size);
std::vector<byte> Memory::m_memory_instruction = makeVector<byte>(max_instruction_size);
std::vector<memory_address> Memory::m_addresses = makeVector<memory_address>(max_address_size);

//initialize counters
unsigned int Memory::m_data_counter = 0;
unsigned int Memory::m_instruction_counter = 0;
unsigned int Memory::m_address_counter = 0;

void Memory::storeData(const std::vector<std::string>& values) {
	//first we read the data from values
	//store any address, for instance x: .word 3 should store mem_address(int,x);
	//store values by distance according to type
	//store in datum
	//values format = [variable][type][datum]

	int counter = 0;// 3 options and need to handle it accordingly
	int type = -1; //help place datum correctly
	bool is_ascii = false;
	for (std::string s : values) {
		if (counter == 0) {
			memory_address mem;
			mem.address = m_data_counter;

			for (char c : s) {
				mem.alias += c;
			}

			m_addresses[m_address_counter++] = mem;
		} 
		if (counter == 1) {
			if (s.find("byte")) {
				type = 0;
				m_data_counter += 1; //move data pointer along to top or back of vector
			} else if (s.find("halfword")) {
				type = 1;
				m_data_counter += 2;
			} else if (s.find("word")) {
				type = 2;
				m_data_counter += 4;
			} else if (s.find("asciiz")) {
				is_ascii = true;
			}
		}
		if (counter == 2 && !is_ascii) {
			if (type == 0) {
				m_memory_data[m_data_counter - 1] = s[0]; //push_back char 
			} else if (type == 1) {
				m_memory_data[m_data_counter - 2] = s[0]; //push_back char 
			} else if (type == 2) {
				m_memory_data[m_data_counter - 4] = (int)s[0]; //push_back char 
			} 
			counter = 0; //reset 
			type = -1;
		}
		if (counter == 2 && is_ascii) {
			for (char c : s) {
				m_memory_data[m_data_counter++] = c;
			}
			is_ascii = false;
			counter = 0; //reset
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
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = 'u';
			m_memory_instruction[m_instruction_counter++] = 's';
			m_memory_instruction[m_instruction_counter++] = 'h';
			++it; // get operand
			for (char c : *it) {
				m_memory_instruction[m_instruction_counter++] = c;
			}
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		} else if (*it == "pop") {
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = 'o';
			m_memory_instruction[m_instruction_counter++] = 'p';
			++it; //get operand
			for (char c : *it) {
				m_memory_instruction[m_instruction_counter++] = c;
			}
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		} else if (*it == "add") {
			m_memory_instruction[m_instruction_counter++] = 'a';
			m_memory_instruction[m_instruction_counter++] = 'd';
			m_memory_instruction[m_instruction_counter++] = 'd';
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		} else if (*it == "mult") {
			m_memory_instruction[m_instruction_counter++] = 'm';
			m_memory_instruction[m_instruction_counter++] = 'u';
			m_memory_instruction[m_instruction_counter++] = 'l';
			m_memory_instruction[m_instruction_counter++] = 't';
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		} else if (*it == "prnt") {
			m_memory_instruction[m_instruction_counter] = 'p';
			m_memory_instruction[m_instruction_counter] = 'r';
			m_memory_instruction[m_instruction_counter] = 'n';
			m_memory_instruction[m_instruction_counter] = 't';
			m_memory_instruction[m_instruction_counter] = '_'; // this is a separator of instructions so if else statements can be avoided
		} else if (*it == "end") {
			m_memory_instruction[m_instruction_counter] = 'e';
			m_memory_instruction[m_instruction_counter] = 'n';
			m_memory_instruction[m_instruction_counter] = 'd';
			m_memory_instruction[m_instruction_counter] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
	}
}

byte* Memory::loadData(const memory_address& mem) {
	byte* result;
	int begin = 0;
	int end = 0;

	// end -begin is size of object we return change to void* return? then execute data!
	//calculate size of data
	for (int i = 0; i < m_addresses.size(); ++i) {
		if (m_addresses[i].alias == mem.alias) {
			begin = m_addresses[i].address;
			end = m_addresses[i+1].address;
			break;
		}
	}

	//get the data
	for (int i = begin; i < end; ++i) {
		result += m_memory_data[i];
	}
}

byte* Memory::loadInstruction(int& location) {
	byte* result;

	while (m_memory_instruction[location] != '_') {
		result += m_memory_instruction[location];
		location++;
	}
	return result;
}

byte* Memory::load(memory_address& addr) {
	if (addr.data_or_instruction) {
		loadData(addr);
	} else {
		loadInstruction(addr.address);
	}
}

void Memory::erase(const int& begin, const int& end) {
	for (int i = begin; i < end; ++i) {
		m_memory_data[i] = '?';
	}
}

void Memory::store(const memory_address& mem_addr) {
	int begin = mem_addr.address;
}

void Memory::store(const int& begin, const int& end, const byte* data) {
	for (int i = begin; i < end; ++i) {
		m_memory_data[i] = data[i];
	}
}

void Memory::store(const memory_address& mem_addr, const byte* data) {
	int begin = 0;
	int end = 0;
	if (mem_addr.data_or_instruction) {
		for (int i = 0; i < m_addresses.size(); ++i) {
			if (m_addresses[i].alias == mem_addr.alias) {
				begin = m_addresses[i].address;
				end = m_addresses[i+1].address;
				erase(begin, end);
				break;
			}
		}
		store(begin, end, data);
	} 
}