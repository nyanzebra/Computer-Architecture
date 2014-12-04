#include "functionInterface.h"
#include "../machine/generalpurposeregistermachine.h"
#include "../logic/logic.h"

//map that stores functions with an opcode as their key
std::unordered_map<int, std::function<void(Instruction& instruction)>> umap_opcodeGroups;

void executeFunction(Instruction& instruction) {
	if (umap_opcodeGroups.size() < 2) {
		initUMapOpcodeGroup();
	}

	umap_opcodeGroups[instruction.opcode](instruction);
}

//determine type
const bool isFloatType(const int& op) {
	return (op > 2 && op < 6 ? true : false);
}

const bool isRType(const int& op) {
	return (op >= 0 && op < 10 ? true : false);
}

const bool isIType(const int& op) {
	return ((op >= 10 && op < 30) ? true : false);
}

const bool isJType(const int& op) {
	return (op >= 30 && op != 31 ? true : false);
}

const bool isBranch(const int& opcode) {
	return (opcode == 0x1E ? true : false);
}

const bool isLoading(const int& opcode) {
	return ((opcode >= 0xC && opcode < 0xF) ? true : false);
}

void fadd(Instruction& instruction) {
	instruction.faluout = Logic<float>::add(instruction.fopA, instruction.fopB);
}

void fsub(Instruction& instruction) {
	instruction.faluout = Logic<float>::sub(instruction.fopA, instruction.fopB);
}

void fmult(Instruction& instruction) {
	instruction.faluout = Logic<float>::mult(instruction.fopA, instruction.fopB);
}

void addR(Instruction& instruction) {
	instruction.aluout = Logic<int>::add(instruction.opA, instruction.opB);
}

void addI(Instruction& instruction) {
	instruction.aluout = Logic<int>::add(instruction.opA, instruction.offset);
}

//i type sub pipeline
void subI(Instruction& instruction) {
	instruction.aluout = Logic<int>::sub(instruction.opA, instruction.offset);
}

void loadAscii(Instruction& instruction) {
	instruction.aluout = instruction.offset;
}

void loadByte(Instruction& instruction) {
	instruction.aluout = Memory::loadData(Logic<int>::add(instruction.opA, instruction.offset));
}

void loadDouble(Instruction& instruction) {
	instruction.faluout = (float) Memory::loadData(Logic<int>::add(instruction.opA, instruction.offset));
}

void storeDouble(Instruction& instruction) {
	Memory::storeFData(Logic<int>::add(instruction.opA,instruction.offset), GPR_Machine::getReg(instruction.rs)+instruction.offset);
}

void insertNOP(Instruction& instruction) {
	instruction.aluout = -1;
	instruction.opcode = 31;
	instruction.offset = -1;
	instruction.opA = -1;
	instruction.opB = -1;
	instruction.rd = -1;
	instruction.rs = -1;
	instruction.rt = -1;
}

//gets the immediate value from Jtype, then sets the pc to that address.
void branch(Instruction& instruction) {
	Base_Machine::setPC(instruction.offset);   //set pc to value(memory location)
}

//breaks up the instruction into Itype values, then checks to see if the source register is equal to 0, then jumps if it is.
void branchEqualZero(Instruction& instruction) {
	if (instruction.opB == 0) { //checks to see if it is equal to 0
		Base_Machine::setPC(instruction.offset); // sets pc to the immediate value
	}
	insertNOP(instruction);
}

//breaks up the instruction into Itype values, then checks to see if the dest register is >= source register 
//then jumps if it is.
void branchGreaterEqual(Instruction& instruction) {
	if (instruction.opB >= instruction.opA) // checks if dest reg is greater or equal to source reg
		Base_Machine::setPC(instruction.offset - 1); //sets pc to immediate
	Scoreboard::setFURegister(instruction.rd, futype::isfree);
	insertNOP(instruction);
}
////breaks up the instruction into Itype values, then checks to see if the dest register is not equal to source register
//then jumps if it is.
void branchNotEqual(Instruction& instruction) {
	if (instruction.opA != instruction.opB) //checks to see if dest reg != source reg
		Base_Machine::setPC(instruction.offset); //set pc to the immediate
	insertNOP(instruction);
}

// Syscall has multiple different internal functions.
// uses registers 29, 30, and 31. 29 is return value / parameter.
void syscall(Instruction& instruction) {
	if (GPR_Machine::getReg(29) == 1) { //print out reg 30
		std::cout << GPR_Machine::getReg(30);
	} else if (GPR_Machine::getReg(29) == 8) { //get user input string
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
	} else if (GPR_Machine::getReg(29) == 4) { //print string that is located in register 30
		int address = GPR_Machine::getReg(30);
		while (Memory::loadData(address)) {
			std::cout << (char)Memory::loadData(address);
			++address;
		}
	} else if (GPR_Machine::getReg(29) == 10) {//exit
		// exit is handled already due to logic check in basemachine.cpp
	}
	insertNOP(instruction);
}

//fills the map with <opcode, function>
void initUMapOpcodeGroup() {
	//r
	umap_opcodeGroups.insert({ 0x0, syscall });

	umap_opcodeGroups.insert({ 0x2, addR });
	umap_opcodeGroups.insert({ 0x3, fadd });
	umap_opcodeGroups.insert({ 0x4, fsub });
	umap_opcodeGroups.insert({ 0x5, fmult });
	//i
	umap_opcodeGroups.insert({ 0xA, addI });
	umap_opcodeGroups.insert({ 0xB, subI });
	umap_opcodeGroups.insert({ 0xC, addI });
	umap_opcodeGroups.insert({ 0xD, addI });
	umap_opcodeGroups.insert({ 0xE, loadAscii });
	umap_opcodeGroups.insert({ 0xF, loadByte });
	umap_opcodeGroups.insert({ 0x10, loadDouble });
	umap_opcodeGroups.insert({ 0x11, storeDouble });

	umap_opcodeGroups.insert({ 0x1B, branchEqualZero });
	umap_opcodeGroups.insert({ 0x1C, branchGreaterEqual });
	umap_opcodeGroups.insert({ 0x1D, branchNotEqual });

	//j
	umap_opcodeGroups.insert({ 0x1E, branch });

	//1F is nop
	umap_opcodeGroups.insert({ 0x1F, insertNOP });
}