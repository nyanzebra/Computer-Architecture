#pragma once
#ifndef FUNCTIONINTERFACE_H
#define FUNCTIONINTERFACE_H

#include <array>
#include <unordered_map>
#include <functional>

#include "types.h"
#include "../machine/generalpurposeregistermachine.h"
#include "../logic/logic.h"

static int instr = 0;

const std::array<int, 4> getRType(const instruction_t& instr) {
	std::array<int, 4> values;
	values[0] = (instr & 0x03E00000) >> 21;
	values[1] = (instr & 0x001F0000) >> 16;
	values[2] = (instr & 0x0000F800) >> 11;
	values[3] = (instr & 0x000007C0) >> 6;
	return values;
};

const std::array<int, 3> getIType(const instruction_t& instr) {
	std::array<int, 3> values;
	values[0] = (instr & 0x03E00000) >> 21;
	values[1] = (instr & 0x001F0000) >> 16;
	values[2] = (instr & 0x0000FFFF);
	return values;
};

const int getJType(const instruction_t& instr) {
	int value = (instr & 0x03FFFFFF);
	return value;
};


std::unordered_map<int, std::function<int()>> umap_opcodeGroups;


int opcodeFunction(const instruction_t& instruction) {
	int opcode = instruction >> 26 ;
	instr = instruction;
	return umap_opcodeGroups[opcode]();
}

int addImmediate() {
	std::array<int, 3> values = getIType(instr);
	int tmp = Logic::add(GPR_Machine::getReg(values[1]), values[2]);
	GPR_Machine::setReg(values[0], tmp);

	if (Base_Machine::isMulticycle()) 
		return 6;
	else
		return 1;
}

int subtractImmediate() {
	std::array<int, 3> values = getIType(instr);
	int tmp = Logic::sub(GPR_Machine::getReg(values[1]), values[2]);
	GPR_Machine::setReg(values[0], tmp);

	if (Base_Machine::isMulticycle())
		return 6;
	else
		return 1;
}

int loadAscii() {
	std::array<int, 3> values = getIType(instr);
	GPR_Machine::setReg(values[0], values[2]);

	if (Base_Machine::isMulticycle())
		return 5;
	else
		return 1;
}

int loadImmediate() {
	std::array<int, 3> values = getIType(instr);
	GPR_Machine::setReg(values[0], values[2]);

	if (Base_Machine::isMulticycle())
		return 3;
	else
		return 1;
}

int loadByte() {
	std::array<int, 3> values = getIType(instr);
	int tmp = Logic::add(GPR_Machine::getReg(values[1]), values[2]);
	GPR_Machine::setReg(values[0], tmp);

	if (Base_Machine::isMulticycle())
		return 6;
	else
		return 1;
}

int loadWord() {
	std::array<int, 3> values = getIType(instr);
	int tmp = Logic::add(GPR_Machine::getReg(values[1]), values[2]);
	GPR_Machine::setReg(values[0], tmp);

	if (Base_Machine::isMulticycle())
		return 6;
	else
		return 1;
}

int branch() {
	int value = getJType(instr);
	Base_Machine::setPC(value);

	if (Base_Machine::isMulticycle())
		return 4;
	else
		return 1;
}

int branchEqualZero() {
	std::array<int, 3> values = getIType(instr);
	if (values[0] == 0)
		Base_Machine::setPC(values[2]);

	if (Base_Machine::isMulticycle())
		return 5;
	else
		return 1;
}

int branchGreaterEqual() {
	std::array<int, 3> values = getIType(instr);
	if (values[0] >= values[1])
		Base_Machine::setPC(values[2]);

	if (Base_Machine::isMulticycle())
		return 5;
	else
		return 1;
}

int branchNotEqual() {
	std::array<int, 3> values = getIType(instr);
	if (values[0] != values[1])
		Base_Machine::setPC(values[2]);

	if (Base_Machine::isMulticycle())
		return 5;
	else
		return 1;
}

// uses registers 29, 30, and 31. 29 is return value / parameter.
int syscall() {

	if (GPR_Machine::getReg(29) == 8) {
		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);
		int address = GPR_Machine::getReg(30);
		int size = GPR_Machine::getReg(31);
		int counter = 0;
		input.substr(0, size);
		// TO DO: hash string, put into memory
	}
	else if (GPR_Machine::getReg(29) == 4) {
		if (Logic::m_hash_strings->find(GPR_Machine::getReg(30)) != Logic::m_hash_strings->end()) {
			std::string s = Logic::m_hash_strings->find(GPR_Machine::getReg(30))-> second;
			if (!s.empty()) {
				std::cout << s;
			}
		}
	}
	else if (GPR_Machine::getReg(29) == 10) {
		// exit is handled alreeady due to logic check in basemachine.cpp
	}

	if (Base_Machine::isMulticycle())
		return 8;
	else
		return 1;
}

void initUMapOpcodeGroup() {
	umap_opcodeGroups.insert(0x0, addImmediate());
	umap_opcodeGroups.insert(0x1, subtractImmediate());
	umap_opcodeGroups.insert(0x2, loadImmediate());
	umap_opcodeGroups.insert(0x3, loadWord());
	umap_opcodeGroups.insert(0x4, loadAscii());
	umap_opcodeGroups.insert(0x5, loadByte());
	umap_opcodeGroups.insert(0x6, branchEqualZero());
	umap_opcodeGroups.insert(0x7, branch());
	umap_opcodeGroups.insert(0x8, branchGreaterEqual());
	umap_opcodeGroups.insert(0x9, branchNotEqual());
	umap_opcodeGroups.insert(0xA, syscall());
}
#endif