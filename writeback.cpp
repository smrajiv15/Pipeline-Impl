#include <cassert>
#include "writeback.h"

WritebackStage::WritebackStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == MEM);
}

void WritebackStage::process() {
	InstructionType it;
	setInstruction(this->prevStage->getInstruction());
	
	it = getInstruction().getType();

	if(it != NOP) {
		incStatistics(FINISHEDINS);
	}

	if(it == HLT) {
		stopSimulation();
	}
	
	this->prevStage->process();
}

WritebackStage::~WritebackStage() {
}
