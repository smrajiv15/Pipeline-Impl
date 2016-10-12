#include <cassert>
#include "writeback.h"

WritebackStage::WritebackStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == MEM);
}

void WritebackStage::process() {
	setInstruction(this->prevStage->getInstruction());
	this->prevStage->process();	
}

WritebackStage::~WritebackStage() {
}
