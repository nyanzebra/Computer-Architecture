#include "memory.h"

//initialize containers
std::vector<byte_t>* Memory::m_data_copy = new std::vector<byte_t>();
std::vector<byte_t> Memory::m_memory_data = L_makebyte_tVector(max_data_size);
std::vector<byte_t> Memory::m_memory_instruction = L_makebyte_tVector(max_instruction_size);
std::vector<memoryAddress_s> Memory::m_addresses = L_makeMemoryAddressVector(max_address_size);

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

	if (m_memory_data.size() == 0) {
		m_memory_data = L_makebyte_tVector(max_data_size);
	}
	if (m_addresses.size() == 0) {
		m_addresses = L_makeMemoryAddressVector(max_address_size);
	}

	int counter = 0;// 3 options and need to handle it accordingly
	int type = 0; //help place datum correctly
	for (std::string s : values) { //for all the data place them in memory correctly
		if (counter == 0) { //put in all aliases and size(induced by locations) in memory address container
			memoryAddress_s* mem = new memoryAddress_s();
			mem->alias = s;
			mem->address = m_data_counter;
			m_addresses[m_address_counter] = *mem;
			m_address_counter += 1;
		}
		if (counter == 1) { //check against type
			if (s == ".byte") {
				type = 0;
			}
			else if (s == ".halfword") {
				type = 1;
			}
			else if (s == ".word") {
				type = 2;
			}
			else if (s == ".asciiz") {
				type = 3;
			}
		}
		if (counter == 2) {
			if (type == 0) {
				m_memory_data[m_data_counter] = s[0]; //push_back char 
				m_data_counter += 1; //move data pointer along to top or back of vector
			}
			else if (type == 1) {
				m_memory_data[m_data_counter] = s[0]; //push_back char 
				m_data_counter += 2;
			}
			else if (type == 2) {
				m_memory_data[m_data_counter] = (int)s[0]; //push_back char 
				m_data_counter += 4;
			}
			else if (type == 3) {
				for (char c : s) { //add all ascii characters
					if (c != '"') {
						m_memory_data[m_data_counter++] = c;
					}
				}
			}
			counter = -1; //reset 
			type = 0; //reset type
		}
		counter++; //move to next item in algorithm
	}
}

void Memory::storeInstruction(const std::vector<std::string>& instructions) {
	//first we read the instructions from instructions
	//TODO: store the instruction pointer for instance main needs an address,sub needs an address
	//instructions format [instruction]<optional>[operand]
	//all instructions will be word size two chars for instruction, two chars for operand
	//for instance push x could be [p][u][o][x] which would read push operand x
	//if reading each as word we should probably have everything as word size?

	if (m_memory_instruction.size() == 0) {
		m_memory_instruction = L_makebyte_tVector(max_instruction_size);
	}

	Memory::machine type;

	for (auto it = instructions.begin(); it != instructions.end(); ++it) {
		if (*it == "push") {
			type = Memory::stackmachine;
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = 'u';
			m_memory_instruction[m_instruction_counter++] = 's';
			m_memory_instruction[m_instruction_counter++] = 'h';
			m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
			++it; // get operand
			for (char c : *it) { //add in the operand of variable size
				m_memory_instruction[m_instruction_counter++] = c;
			}
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
		else if (*it == "pop") {
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = 'o';
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
			++it; //get operand
			for (char c : *it) { //add in the operand of variable size
				m_memory_instruction[m_instruction_counter++] = c;
			}
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
		if (*it == "stor") {
			m_memory_instruction[m_instruction_counter++] = 's';
			m_memory_instruction[m_instruction_counter++] = 't';
			m_memory_instruction[m_instruction_counter++] = 'o';
			m_memory_instruction[m_instruction_counter++] = 'r';
			m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
			++it; // get operand
			for (char c : *it) { //add in the operand of variable size
				m_memory_instruction[m_instruction_counter++] = c;
			}
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
		else if (*it == "load") {
			type = Memory::accummachine;
			m_memory_instruction[m_instruction_counter++] = 'l';
			m_memory_instruction[m_instruction_counter++] = 'o';
			m_memory_instruction[m_instruction_counter++] = 'a';
			m_memory_instruction[m_instruction_counter++] = 'd';
			m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
			++it; //get operand
			for (char c : *it) { //add in the operand of variable size
				m_memory_instruction[m_instruction_counter++] = c;
			}
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
		else if (*it == "add") {
			m_memory_instruction[m_instruction_counter++] = 'a';
			m_memory_instruction[m_instruction_counter++] = 'd';
			m_memory_instruction[m_instruction_counter++] = 'd';
			if (type != Memory::accummachine){
				m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
			}
			else {
				m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
				++it; //get operand
				for (char c : *it) { //add in the operand of variable size
					m_memory_instruction[m_instruction_counter++] = c;
				}
				m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
			}
		}
		else if (*it == "mult") {
			m_memory_instruction[m_instruction_counter++] = 'm';
			m_memory_instruction[m_instruction_counter++] = 'u';
			m_memory_instruction[m_instruction_counter++] = 'l';
			m_memory_instruction[m_instruction_counter++] = 't';
			if (type != Memory::accummachine){
				m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
			}
			else {
				m_memory_instruction[m_instruction_counter++] = '`'; // this is a separator of instructions so if else statements can be avoided
				++it; //get operand
				for (char c : *it) { //add in the operand of variable size
					m_memory_instruction[m_instruction_counter++] = c;
				}
				m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
			}
		}
		else if (*it == "prnt") {
			m_memory_instruction[m_instruction_counter++] = 'p';
			m_memory_instruction[m_instruction_counter++] = 'r';
			m_memory_instruction[m_instruction_counter++] = 'n';
			m_memory_instruction[m_instruction_counter++] = 't';
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
		else if (*it == "end") {
			m_memory_instruction[m_instruction_counter++] = 'e';
			m_memory_instruction[m_instruction_counter++] = 'n';
			m_memory_instruction[m_instruction_counter++] = 'd';
			m_memory_instruction[m_instruction_counter++] = '_'; // this is a separator of instructions so if else statements can be avoided
		}
	}
}

std::list<byte_t> Memory::loadData(const byte_t* mem) {
	int begin = 0;
	int end = 0;

	// end - begin is size of object we return
	//calculate size of data
	for (unsigned int i = 0; i < m_addresses.size(); ++i) {
		if (m_addresses[i].alias == mem) {
			begin = m_addresses[i].address;
			end = m_addresses[i + 1].address;
			break;
		}
	}

	int j = begin;
	if (end < begin) { //catch data that may be at the end and have null contents after
		while (m_memory_data[j]) {
			end = j + 1;
			++j;
		}
	}

	//get the data
	std::list<byte_t> temp;
	for (int i = begin; i < end; ++i) {
		temp.push_back(m_memory_data[i]);
	}
	return temp;
}

std::list<byte_t> Memory::loadData(const memoryAddress_s& mem) {
	std::list<byte_t> result;
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

	int j = begin;
	if (end < begin) { //catch data that may be at the end and have null contents after
		while (m_memory_data[j]) {
			end = j + 1;
			++j;
		}
	}

	//get the data
	for (int i = begin; i < end; ++i) {
		result.push_back(m_memory_data[i]);
	}

	return result;
}

std::list<byte_t> Memory::loadInstruction(unsigned int& location) {
	std::list<byte_t> result;

	while (m_memory_instruction[location] != '_') { //our nice separator! 
		result.push_back(m_memory_instruction[location++]);//get the instruction word
	}
	location++;

	return result;
}

void Memory::erase(const int& begin, const int& end) {
	for (int i = begin; i < end; ++i) { //insert null in range of begin->end
		m_memory_data[i] = '\0';
	}
}

void Memory::store(const int& begin, const int& end, const std::list<byte_t>& data) {
	if (begin == end) { //obviously...
		return;
	}

	int size = data.size();
	std::string s = L_listToString(data);//mainly for operator[]
	int pchar = 0;

	for (int i = begin; i < begin + size; ++i) {//insert all the data!
		m_memory_data[i] = s[pchar++];
	}


	for (int i = begin + size; i < end; ++i) {//still got space? no problem, insert null!
		m_memory_data[i] = '\0';
	}
}

void Memory::storeData(const memoryAddress_s& mem_addr, const std::list<byte_t>& data) {
	int begin = 0;
	int end = 0;
	for (unsigned int i = 0; i < m_addresses.size(); ++i) { //a higher level of abstraction for storing the data
		if (m_addresses[i].alias == mem_addr.alias) {
			begin = m_addresses[i].address;
			end = m_addresses[i+1].address;
			erase(begin, end); //erase what was there before
			break;
		}
		store(begin, end, data); //store the new data
	} 
}

void Memory::storeData(const byte_t* mem_addr, const std::list<byte_t>& data) {
	int begin = 0;
	int end = 0;
	for (unsigned int i = 0; i < m_addresses.size(); ++i) {//a higher level of abstraction for storing the data
		if (m_addresses[i].alias == mem_addr) {
			begin = m_addresses[i].address;
			end = m_addresses[i + 1].address;
			erase(begin, end); //erase what was there before
			break;
		}
	}
	store(begin, end, data);//store the new data
}