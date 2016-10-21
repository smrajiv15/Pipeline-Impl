#include <cassert>
#include "instruction.h"

void Instruction::init(InstructionType _type, RegisterType _arg1, RegisterType _arg2, RegisterType _arg3, 
                       int _immidiate, int _address) {
  type = _type;
  arg1 = _arg1;
  arg2 = _arg2;
  arg3 = _arg3;
  immidiate = _immidiate;
  address = _address;
  A = B = 0;
  aluOut = 0;
  loadMemData = 0;
  fetchedAtCycle = 0;
  srcCycle1 = 0;
  srcCycle2 = 0;
}

Instruction::Instruction() {
  init(NOP, R0, R0, R0, 0, 0);
}

Instruction::Instruction(InstructionType _type, int _address) {
  init(_type, R0, R0, R0, 0, _address);
}

Instruction::Instruction(InstructionType _type, RegisterType _arg1, int _immidiate, int _address) {
  init(_type, _arg1, R0, R0, _immidiate, _address);
}

Instruction::Instruction(InstructionType _type, RegisterType _arg1, RegisterType _arg2, 
                         int _immidiate, int _address) {
  init(_type, _arg1, _arg2, R0, _immidiate, _address);
}

Instruction::Instruction(InstructionType _type, RegisterType _arg1, RegisterType _arg2, 
                         RegisterType _arg3, int _address) {
  init(_type, _arg1, _arg2, _arg3, 0, _address);
}

Instruction::Instruction(Instruction& inst) {
  init(inst.type, inst.arg1, inst.arg2, inst.arg3, inst.immidiate, inst.address);
  A = inst.A;
  B = inst.B;
  aluOut = inst.aluOut;
  loadMemData = inst.loadMemData;
  fetchedAtCycle = inst.fetchedAtCycle;
  srcCycle1 = inst.srcCycle1;
  srcCycle2 = inst.srcCycle2;
}

Instruction& Instruction::operator=(Instruction& rhs) {
  if (this == &rhs)
    return *this;
  init(rhs.type, rhs.arg1, rhs.arg2, rhs.arg3, rhs.immidiate, rhs.address);
  A = rhs.A;
  B = rhs.B;
  aluOut = rhs.aluOut;
  loadMemData = rhs.loadMemData;
  fetchedAtCycle = rhs.fetchedAtCycle;
  srcCycle1 = rhs.srcCycle1;
  srcCycle2 = rhs.srcCycle2;
  return *this;
}

void Instruction::clear() {
  init(NOP, R0, R0, R0, 0, 0);
}

// Returns whether dest instruction is data dependent on src
// This should be used for detecting hazard between in ID stage
// instruction and later stage instruction
bool Instruction::isDataDependent(Instruction& src, Instruction& dest) {

  bool is_dep = false;
	int fet_cycle = dest.getFetchedAtCycle();

	if(dest.isAluImm() || dest.isAluReg() || dest.getType() == LD) { // if destination is ALU IMM & ALU REG
		if(src.isAluReg()) {
			if(src.getArg2() == dest.getArg1()) {
				src.setSrcCycle1(fet_cycle);	
				is_dep = true;
			} 
			if(src.getArg3() == dest.getArg1()) {
				src.setSrcCycle2(fet_cycle);
				is_dep = true;
			}
		} else if(src.isAluImm()) {
			if(src.getArg2() == dest.getArg1()) {
				src.setSrcCycle1(fet_cycle);
				is_dep = true;
			}
		} else if(src.isBranch()) {
			if(src.getArg1() == dest.getArg1()) {
				src.setSrcCycle1(fet_cycle);
				is_dep = true;
			}
		} else if(src.isMemory()) {
			if(src.getType() == LD) {
				if(src.getArg2() == dest.getArg1()) {
					src.setSrcCycle1(fet_cycle);
					is_dep = true;
				}
			} else { //store instruction
				if(src.getArg1() == dest.getArg1()) {
					src.setSrcCycle1(fet_cycle);
					is_dep = true;
				}

				if(src.getArg2() == dest.getArg1()) {
					src.setSrcCycle2(fet_cycle);
					is_dep = true;
				}
			}
		}		
	
	return is_dep;
	}
}

Instruction::~Instruction() {
}
