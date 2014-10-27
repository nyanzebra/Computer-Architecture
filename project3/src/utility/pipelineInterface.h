#pragma once
#ifndef PIPELINEINTERFACE_H
#define PIPELINEINTERFACE_H

#include "functionInterface.h"
#include "latches.h"

const latch_decode_execute decode() {
	latch_decode_execute new_decode_execute;

	new_decode_execute.opcode = instr >> 26;

	if (isIType(new_decode_execute.opcode)) {
		new_decode_execute.op_A = GPR_Machine::getReg(getIType(instr)[0]);
		new_decode_execute.op_B = GPR_Machine::getReg(getIType(instr)[1]);
		if (isLoading(new_decode_execute.opcode)) {// maybe needs to be changed
			new_decode_execute.op_B = getIType(instr)[1];
		}
		new_decode_execute.rs = getIType(instr)[0];
		new_decode_execute.rt = getIType(instr)[1];
		new_decode_execute.rd = getIType(instr)[1];
		new_decode_execute.alu_out = (getIType(instr)[2]);
		new_decode_execute.offset = new_decode_execute.alu_out;
	} else if (isRType(new_decode_execute.opcode)) {
		new_decode_execute.op_A = GPR_Machine::getReg(getRType(instr)[0]);
		new_decode_execute.op_B = GPR_Machine::getReg(getRType(instr)[1]);
		new_decode_execute.rs = getRType(instr)[0];
		new_decode_execute.rt = getRType(instr)[1];
		new_decode_execute.rd = getRType(instr)[2];
		new_decode_execute.alu_out = (getRType(instr)[3]);
	} else if (isJType(new_decode_execute.opcode)) {
		umap_opcodeGroups[new_decode_execute.opcode]();
		new_decode_execute.opcode = -1;
		new_decode_execute.alu_out = -1;
		new_decode_execute.offset = -1;
		new_decode_execute.op_A = -1;
		new_decode_execute.op_B = -1;
		new_decode_execute.rd = -1;
		new_decode_execute.rs = -1;
		new_decode_execute.rt = -1;
		return new_decode_execute;
	}

	return new_decode_execute;
}

//gets the opcode and then checks to see if it is in the map, then exectues the function if it is in the map.
const latch_execute_memory executeInstruction() {
	if (umap_opcodeGroups.size() == 0) { //just in case it is not init
		initUMapOpcodeGroup();
	}

	//check execute hazard
	if (latch_decode_execute_old.rs == latch_execute_memory_old.rd) {
		latch_decode_execute_old.op_A = latch_execute_memory_old.alu_out;
	}

	if (latch_execute_memory_old.rd == latch_decode_execute_old.rt) {
		latch_decode_execute_old.op_B = latch_execute_memory_old.alu_out;
	}

	//check memory hazard
	if (latch_decode_execute_old.rs == latch_memory_writeback_new.rd) {
		latch_decode_execute_old.op_A = latch_memory_writeback_new.alu_out;
	}

	if (latch_memory_writeback_new.rd == latch_decode_execute_old.rt) {
		latch_decode_execute_old.op_B = latch_memory_writeback_new.alu_out;
	}
	if (latch_decode_execute_old.opcode != -1) {
		if (latch_decode_execute_old.opcode == 31) {
			Base_Machine::incrementNopCount();
		}
		umap_opcodeGroups[latch_decode_execute_old.opcode]();
	}
	latch_execute_memory new_execute_memory;
	new_execute_memory.opcode = latch_decode_execute_old.opcode;
	new_execute_memory.op_B = latch_decode_execute_old.op_B;
	new_execute_memory.alu_out = latch_decode_execute_old.alu_out;
	new_execute_memory.rd = latch_decode_execute_old.rd;
	if (isIType(new_execute_memory.opcode)) {
		new_execute_memory.rd = latch_decode_execute_old.rt;
	}
	return new_execute_memory;
}

const latch_memory_writeback pipelineMemory() {
	latch_memory_writeback new_memory_writeback;

	new_memory_writeback.alu_out = latch_execute_memory_old.alu_out; //rtype
	new_memory_writeback.opcode = latch_execute_memory_old.opcode;//always
	new_memory_writeback.op_B = latch_execute_memory_old.op_B;//for loads
	new_memory_writeback.rd = latch_execute_memory_old.rd;//rtype
	new_memory_writeback.mdr = latch_execute_memory_old.alu_out; //target memory
	return new_memory_writeback;
}

const int writeback() {
	if (isRType(latch_memory_writeback_old.opcode) || isIType(latch_memory_writeback_old.opcode)) {
		GPR_Machine::setReg(latch_memory_writeback_old.rd, latch_memory_writeback_old.mdr);
	}

	return 0;
}

#endif