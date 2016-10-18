#include <cassert>
#include "memaccess.h"

MemaccessStage::MemaccessStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == EX);
}

void MemaccessStage::process() {

	setInstruction(prevStage->getInstruction());
	Instruction inst = getInstruction();

	if(inst.isLoad()) {

		inst.setLoadMemData(getData(inst.getAluOut()));

	} else if(inst.isStore()) {

		int reg_val = 0;
		reg_val = getReg(inst.getArg1());
		setData(inst.getAluOut(), reg_val);	

	} else if(inst.isBranch()) {
		if(inst.getA() == 0 || inst.getA() != 0) {
			setPc(getPc() + inst.getAluOut());
		}
	}

	setInstruction(inst);
	prevStage->process();	
}

MemaccessStage::~MemaccessStage() {
}
