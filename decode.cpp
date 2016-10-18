#include <cassert>
#include "decode.h"

#include<typeinfo>

int halt_set;

DecodeStage::DecodeStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == IF);
}

void DecodeStage::process() {	
			
	Instruction inst;
	InstructionType it;

	setInstruction(prevStage->getInstruction());
	it = getInstruction().getType();

	if(it == HLT) {
		prevStage->setInstruction(inst);
		halt_set = 1;
		return;
	}

	if(halt_set && it == NOP) {
		prevStage->setInstruction(inst);
		return;
	}

	inst = getInstruction();

	if(inst.isAluReg()) {

		inst.setA(getReg(inst.getArg2()));
		inst.setB(getReg(inst.getArg3()));

	} else if(inst.isAluImm()) {
		
		inst.setA(getReg(inst.getArg2()));
		inst.setB(inst.getImmidiate());	

	} else if(inst.isMemory()) {

		inst.setA(getReg(inst.getArg2()));
		inst.setB(inst.getImmidiate());	

	} else if(inst.isBranch()) {
		
		inst.setA(getReg(inst.getArg1()));
		inst.setB(inst.getImmidiate());
	
	}

	setInstruction(inst);	
	prevStage->process();
}

DecodeStage::~DecodeStage() {
}
