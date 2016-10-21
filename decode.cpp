#include <cassert>
#include "decode.h"

#include<typeinfo>

int branch_found = 0;

DecodeStage::DecodeStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == IF);
}

void DecodeStage::process() {	
			
	Instruction inst;
	InstructionType it;
	AbstractStage *st = nextStage;
	AbstractStage *wb_stage = NULL;
	bool dep_res = false;

	if(!isStalled()) {
		setInstruction(prevStage->getInstruction());
	}

	it = getInstruction().getType();
	inst = getInstruction();
	
	
	if(isStalled()) {
		wb_stage = nextStage->getNextStage()->getNextStage();
		
		if(inst.getSrcCycle1()) {
			if(wb_stage->updateDependences(inst.getSrcCycle1())) {
				inst.setSrcCycle1(0);
			}
		}

		if(inst.getSrcCycle2()) {
				if(wb_stage->updateDependences(inst.getSrcCycle2())) {
				inst.setSrcCycle2(0);
			}
		}

		setInstruction(inst);

		if(inst.getSrcCycle2() || inst.getSrcCycle1()) {		
			incStatistics(STALLCYCLE);	
			prevStage->process();
			return;
		} else {
			setUnstalled();
			dep_res = true;
			goto fetch_op;
		}
	}

	//check for the first time in the decode stage whether the dep exists
	while(st != NULL && st->getType() != WR) {
		Instruction nxt_inst = st->getInstruction();
		if(nxt_inst.getType() && inst.getType() && inst.isDataDependent(nxt_inst)) {
			incStatistics(STALLCYCLE);
			setStalled();
			setInstruction(inst);
			return;
		}
		st = st->getNextStage();
	}

fetch_op:

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
		branch_found = 1;	
	}

	setInstruction(inst);
	prevStage->process();
}

DecodeStage::~DecodeStage() {
}
