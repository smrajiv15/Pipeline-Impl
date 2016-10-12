#include <cassert>
#include "decode.h"

#include<typeinfo>

DecodeStage::DecodeStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == IF);
}

void DecodeStage::process() {	
			
	Instruction inst;
	InstructionType it;

	setInstruction(this->prevStage->getInstruction());
	it = getInstruction().getType();

	if(it == HLT || it == NOP) {
		this->prevStage->setInstruction(inst);
		return;
	}
		
	this->prevStage->process();
}

DecodeStage::~DecodeStage() {
}
