#include <cassert>
#include "execute.h"

ExecuteStage::ExecuteStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == ID);
}

void ExecuteStage::process() {
	setInstruction(this->prevStage->getInstruction());
	this->prevStage->process();	
}

ExecuteStage::~ExecuteStage() {
}
