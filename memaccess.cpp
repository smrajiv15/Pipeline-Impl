#include <cassert>
#include "memaccess.h"

extern int branch_found;

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
		if(((inst.getA() == 0) && (inst.getType() == BEQZ)) || ((inst.getA() != 0) && (inst.getType() == BNEQZ))) {
				setPc(getPc() + inst.getAluOut());
		}
		branch_found = 0;
	}

	cout << "MEM: " << inst.getType() << "CC: " << getCycle() << endl;
	setInstruction(inst);
	prevStage->process();	
}

MemaccessStage::~MemaccessStage() {
}
