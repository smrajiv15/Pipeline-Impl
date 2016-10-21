#include <cassert>
#include "fetch.h"

int halt_flag = 0;
extern int branch_found;

FetchStage::FetchStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage == NULL);
}

void FetchStage::process() {
  // process for this step
  int cur_pc = getPc();

	if(isStalled()) {
		return;
	}
	
	if(!halt_flag) {
		setInstruction(getNextIns());
	} 

	if(branch_found == 1) {
		Instruction ins;
		setInstruction(ins);
		incStatistics(STALLCYCLE);
		return;
	}

	if(halt_flag) {
		incStatistics(STALLCYCLE);
	}	

	if(getInstruction().getType() == HLT) {
		halt_flag = 1;
	}

	getInstruction().setFetchedAtCycle(getCycle());		
	cur_pc += 4;
	setPc(cur_pc);
}

FetchStage::~FetchStage() {
}
