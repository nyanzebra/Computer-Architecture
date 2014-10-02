#pragma once
#ifndef FUNCTIONINTERFACE_H
#define FUNCTIONINTERFACE_H

#include <array>
#include <unordered_map>
#include <functional>

#include "types.h"
#include "../machine/generalpurposeregistermachine.h"
#include "../logic/logic.h"

//variable that holds the current instruction, set by opcodeFunction
static int instr = 0;


//Breaks up the instruction into 4 different values and returns them in an array.
const std::array<int, 4> getRType(const instruction_t& instr) {
	std::array<int, 4> values;
	values[0] = (instr & 0x03E00000) >> 21; //source reg1
	values[1] = (instr & 0x001F0000) >> 16; //source reg2
	values[2] = (instr & 0x0000F800) >> 11; //dest reg
	values[3] = (instr & 0x000007C0) >> 6;  //shift value
	return values;
};

//Breaks up the instruction into 3 different values and returns them in an array.
const std::array<int, 3> getIType(const instruction_t& instr) {
	std::array<int, 3> values;
	values[0] = (instr & 0x03E00000) >> 21; //source reg
	values[1] = (instr & 0x001F0000) >> 16; //dest reg
	values[2] = (instr & 0x0000FFFF);       //imm value
	return values;
};

//returns the immediate value that is stored in J type instructions
const int getJType(const instruction_t& instr) {
	int value = (instr & 0x03FFFFFF);       //immediate value
	return value;
};

//map that stores functions with an opcode as their key
std::unordered_map<int, std::function<int()>> umap_opcodeGroups;

//breaks up the instruction to get Itype values, then adds the source and immediate together.
//Then sets the dest reg to the calculated value.
int addImmediate() {
	std::array<int, 3> values = getIType(instr); //breaks up instruction using Itype
	int tmp = Logic::add(GPR_Machine::getReg(values[0]), values[2]); //calculate the source reg value added to the immediate
	GPR_Machine::setReg(values[1], tmp); //store tmp into the dest register

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 6;
	else
		return 1;
}

//breaks up the instruction to get Itype values, then subtracts the source by the immediate.
//Then sets the dest reg to the calculated value.
int subtractImmediate() {
	std::array<int, 3> values = getIType(instr); //breaks up instruction using Itype
	int tmp = Logic::sub(GPR_Machine::getReg(values[0]), values[2]);//calculate the source reg value subtracted by the immediate
	GPR_Machine::setReg(values[1], tmp); //store tmp into the dest register

	if (Base_Machine::isMulticycle()) 
		return 6;
	else
		return 1;
}

//breaks up the instruction to get Itype values
//Then sets the dest reg to the immediate value.
int loadAscii() {
	std::array<int, 3> values = getIType(instr); //breaks up instruction using Itype
	GPR_Machine::setReg(values[1], values[2]);   //store immediate into the dest register

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 5;
	else
		return 1;
}

//breaks up the instruction to get Itype values
//Then sets the dest reg to the immediate value.
int loadImmediate() {
	std::array<int, 3> values = getIType(instr); //breaks up instruction using Itype
	GPR_Machine::setReg(values[1], values[2]);   //store immediate into the dest register

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 3;
	else
		return 1;
}

//breaks up the instruction to get Itype values
//Then sets the dest reg to the source register + offset.
int loadByte() {
	std::array<int, 3> values = getIType(instr);                     //breaks up instruction using Itype
	int tmp = Logic::add(GPR_Machine::getReg(values[0]), values[2]); // adds the offset to the source reg
	GPR_Machine::setReg(values[1], tmp);                             //store tmp into dest register

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 6;
	else
		return 1;
}

//currently not in use
int loadWord() {
	std::array<int, 3> values = getIType(instr);
	int tmp = Logic::add(GPR_Machine::getReg(values[0]), values[2]);
	GPR_Machine::setReg(values[1], tmp);

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 6;
	else
		return 1;
}

//gets the immediate value from Jtype, then sets the pc to that address.
int branch() {
	int value = getJType(instr);  //get jType value
	Base_Machine::setPC(value);   //set pc to value(memory location)

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 4;
	else
		return 1;
}

//breaks up the instruction into Itype values, then checks to see if the source register is equal to 0, then jumps if it is.
int branchEqualZero() {
	std::array<int, 3> values = getIType(instr); //get Itype values
	if (Memory::loadData(GPR_Machine::getReg(values[1])) == 0) { //checks to see if it is equal to 0
		Base_Machine::setPC(values[2]); // sets pc to the immediate value
	}

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 5;
	else
		return 1;
}

//breaks up the instruction into Itype values, then checks to see if the dest register is >= source register 
//then jumps if it is.
int branchGreaterEqual() {
	std::array<int, 3> values = getIType(instr); //get Itype values
	if (GPR_Machine::getReg(values[1]) >= GPR_Machine::getReg(values[0])) // checks if dest reg is greater or equal to source reg
		Base_Machine::setPC(values[2]); //sets pc to immediate

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 5;
	else
		return 1;
}
////breaks up the instruction into Itype values, then checks to see if the dest register is not equal to source register
//then jumps if it is.
int branchNotEqual() {
	std::array<int, 3> values = getIType(instr); //get Itype values
	if (Memory::loadData(GPR_Machine::getReg(values[1])) != Memory::loadData(GPR_Machine::getReg(values[0]))) //checks to see if dest reg != source reg
		Base_Machine::setPC(values[2]); //set pc to the immediate

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 5;
	else
		return 1;
}

// Syscall has multiple different internal functions.
// uses registers 29, 30, and 31. 29 is return value / parameter.
int syscall() {
	
	//get user input string
	if (GPR_Machine::getReg(29) == 8) {
		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);
		int address = GPR_Machine::getReg(30);
		int size = GPR_Machine::getReg(31);
		int counter = 0;
		input.substr(0, size);

		for (char c : input) {
			Memory::storeData(address, c);
			address++;
		}
	} 
	//print string that is located in register 30
	else if (GPR_Machine::getReg(29) == 4) {
		if (Logic::m_hash_strings->find(Memory::loadData(GPR_Machine::getReg(30))) != Logic::m_hash_strings->end()) {
			std::string s = Logic::m_hash_strings->find(Memory::loadData(GPR_Machine::getReg(30)))->second;
			if (!s.empty()) {
				std::cout << s;
			}
		}
	} 
	//exit
	else if (GPR_Machine::getReg(29) == 10) {
		// exit is handled already due to logic check in basemachine.cpp
	}

	if (Base_Machine::isMulticycle()) //checks global boolean to see if the machien is a multicycle
		return 8;
	else
		return 1;
}

//fills the map with <opcode, function>
void initUMapOpcodeGroup() {
	umap_opcodeGroups.insert({ 0x0, addImmediate });
	umap_opcodeGroups.insert({ 0x1, subtractImmediate });
	umap_opcodeGroups.insert({ 0x2, loadImmediate });
	umap_opcodeGroups.insert({ 0x3, loadWord });
	umap_opcodeGroups.insert({ 0x4, loadAscii });
	umap_opcodeGroups.insert({ 0x5, loadByte });
	umap_opcodeGroups.insert({ 0x6, branchEqualZero });
	umap_opcodeGroups.insert({ 0x7, branch });
	umap_opcodeGroups.insert({ 0x8, branchGreaterEqual });
	umap_opcodeGroups.insert({ 0x9, branchNotEqual });
	umap_opcodeGroups.insert({ 0xA, syscall });
}

//gets the opcode and then checks to see if it is in the map, then exectues the function if it is in the map.
int opcodeFunction(const instruction_t& instruction) {
	if (umap_opcodeGroups.size() == 0) { //just in case it is not init
		initUMapOpcodeGroup();
	}
	int opcode = instruction >> 26;
	instr = instruction;
	return umap_opcodeGroups[opcode]();
}
#endif
