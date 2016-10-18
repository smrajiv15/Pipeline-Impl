#include <cassert>
#include "execute.h"

ExecuteStage::ExecuteStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == ID);
}

void ExecuteStage::process() {
	setInstruction(prevStage->getInstruction());
	Instruction inst = getInstruction();
	InstructionType it = inst.getType();
	int a = inst.getA(); 
	int b = inst.getB();
	int res = 0;
	
	if(inst.isAluReg()) {
		if(it == ADD) {
			res = a + b;
		} else if(it == SUB) {
			res = a - b;
		} else if(it == MUL) {
			res = a * b;
		} else if(it == DIV) {
			if(b != 0) {
				res = a / b;
			}
		} else if(it == XOR) {
		 	res = a ^ b;	
		} else if(it == AND) {
			res = a & b;
		} else if(it == OR) {
			res = a | b;
		}
	} else if(inst.isAluImm()) {
		if(it == ADDI) {
			res = a + b;
		}	else if(it == SUBI) {
			res = a - b;
		}
	} else if(inst.isMemory()) {
		res = a + b;
	}	else if(inst.isBranch()) {
		res = b * 4;
	}
		
	inst.setAluOut(res);
	setInstruction(inst);
	prevStage->process();	
}

ExecuteStage::~ExecuteStage() {
}
