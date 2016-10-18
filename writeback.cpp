#include <cassert>
#include "writeback.h"

WritebackStage::WritebackStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == MEM);
}

void WritebackStage::process() {

	setInstruction(prevStage->getInstruction());
	Instruction inst = getInstruction();

	if(inst.isAluReg() || inst.isAluImm()) {
		setReg(inst.getArg1(), inst.getAluOut());
	} else if(inst.isLoad()) {
		setReg(inst.getArg1(), inst.getLoadMemData());
	}

	if(!inst.isNop()) {
		incStatistics(FINISHEDINS);
	}

	if(inst.isHlt()) {
		stopSimulation();
	}
	
	setInstruction(inst);	
	prevStage->process();
}

WritebackStage::~WritebackStage() {
}
