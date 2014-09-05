#include "memory.h"
#include "../utility/lambdas.h"

//initialize containers
std::vector<byte> Memory::m_memory_data = L_makeByteVector(max_data_size);
std::vector<byte> Memory::m_memory_instruction = L_makeByteVector(max_instruction_size);
std::vector<memory_address> Memory::m_addresses = L_makeMemoryAddressVector(max_address_size);

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
	int type = 0; //help place datum correctly
	bool is_ascii = false;
	for (std::string s : values) {
		if (counter == 0) {
			memory_address* mem = new memory_address();
			mem->alias = s;
			mem->data_or_instruction = true;
			mem->address = m_data_counter;
			m_addresses[m_address_counter] = *mem;
			m_address_counter += 1;
		} 
		if (counter == 1) {
			if (s == ".byte") {
				type = 0;
			} else if (s == ".halfword") {
				type = 1;
			} else if (s == ".word") {
				type = 2;
			} else if (s == ".asciiz") {
				is_ascii = true;
			}
		}
		if (counter == 2 && !is_ascii) {
			if (type == 0) {
				m_memory_data[m_data_counter] = s[0]; //push_back char 
				m_data_counter += 1; //move data pointer along to top or back of vector
			} else if (type == 1) {
				m_memory_data[m_data_counter] = s[0]; //push_back char 
				m_data_counter += 2;
			} else if (type == 2) {
				m_memory_data[m_data_counter] = (int)s[0]; //push_back char 
				m_data_counter += 4;
			} 
			counter = -1; //reset 
			type = 0;
		}
		if (counter == 2 && is_ascii) {
			for (char c : s) {
				if (c != '"') {
					m_memory_data[m_data_counter++] = c;
				}
			}
			is_ascii = false;
			counter = -1; //reset
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
			m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
			++it; // get operand
			for (char c : *it) {
				m_memory_instruction[m_instruction_counter++] = c;
			}
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		} else if (*it == "pop") {
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = 'o';
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
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
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = 'r';
			m_memory_instruction[m_instruction_counter++] = 'n';
			m_memory_instruction[m_instruction_counter++] = 't';
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		} else if (*it == "end") {
			m_memory_instruction[m_instruction_counter++] = 'e';
			m_memory_instruction[m_instruction_counter++] = 'n';
			m_memory_instruction[m_instruction_counter++] = 'd';
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
	}
}

std::list<byte> Memory::loadData(const byte* mem) {
	int begin = 0;
	int end = 0;

	// end -begin is size of object we return change to void* return? then execute data!
	//calculate size of data
	for (unsigned int i = 0; i < m_addresses.size(); ++i) {
		if (m_addresses[i].alias == mem) {
			begin = m_addresses[i].address;
			end = m_addresses[i + 1].address;
			break;
		}
	}

	int j = begin;
	if (end < begin) {
		while (m_memory_data[j]) {
			end = j + 1;
			++j;
		}
	}

	//get the data
	std::list<byte> temp;
	for (int i = begin; i < end; ++i) {
		temp.push_back(m_memory_data[i]);
	}
	return temp;
}

std::list<byte> Memory::loadData(const memory_address& mem) {
	std::list<byte> result;
	int begin = 0;
	int end = 0;

	// end -begin is size of object we return change to void* return? then execute data!
	//calculate size of data
	for (unsigned int i = 0; i < m_addresses.size(); ++i) {
		if (m_addresses[i].alias == mem.alias) {
			begin = m_addresses[i].address;
			end = m_addresses[i+1].address;
			break;
		}
	}

	//get the data
	for (int i = begin; i < end; ++i) {
		result.push_back(m_memory_data[i]);
	}

	return result;
}

std::list<byte> Memory::loadInstruction(int& location) {
	std::list<byte> result;

	while (m_memory_instruction[location] != '_') {
		result.push_back(m_memory_instruction[location]);
		location++;
	}
	location++;

	return result;
}

std::list<byte> Memory::load(memory_address& addr) {
	if (addr.data_or_instruction) {
		return loadData(addr);
	} else {
		return loadInstruction(addr.address);
	}
}

void Memory::erase(const int& begin, const int& end) {
	for (int i = begin; i < end; ++i) {
		m_memory_data[i] = '\0';
	}
}

void Memory::store(const std::list<byte>& data) {
	int begin = m_data_counter + 4;
	int end = begin + data.size();
	m_data_counter += data.size();
	memory_address mem;
	mem.alias = "temp";
	mem.address = begin;
	mem.data_or_instruction = true;
	m_addresses[m_address_counter] = mem;
	m_address_counter++;
	store(begin, end, data);
}

void Memory::store(const byte* mem_addr0, const byte* mem_addr1) {
	int begin = 0;
	int end = 0;
	std::list<byte> data;
	for (unsigned int i = 0; i < m_addresses.size(); ++i) {
		if (m_addresses[i].alias == mem_addr0) {
			begin = m_addresses[i].address;
		}
		if (m_addresses[i].alias == mem_addr1) {
			end = m_addresses[i].address;
		}
	}

	for (int i = begin; i < end; ++i) {
		data.push_back(m_memory_data[i]);
	}

	store(begin, end, data);
}

void Memory::store(const int& begin, const int& end, const std::list<byte>& data) {
	if (begin == end) {
		return;
	}

	int size = data.size();
	std::string s = L_listToString(data);
	int pchar = 0;

	for (int i = begin; i < begin + size; ++i) {
		m_memory_data[i] = s[pchar++];
	}


	for (int i = begin + size; i < end; ++i) {
		m_memory_data[i] = '\0';
	}
}

void Memory::store(const memory_address& mem_addr, const std::list<byte>& data) {
	int begin = 0;
	int end = 0;
	if (mem_addr.data_or_instruction) {
		for (unsigned int i = 0; i < m_addresses.size(); ++i) {
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

void Memory::storeData(const byte* mem_addr, const std::list<byte>& data) {
	int begin = 0;
	int end = 0;
	for (unsigned int i = 0; i < m_addresses.size(); ++i) {
		if (m_addresses[i].alias == mem_addr) {
			begin = m_addresses[i].address;
			end = m_addresses[i + 1].address;
			erase(begin, end);
			break;
		}
	}
	store(begin, end, data);
}