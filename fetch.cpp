#include <cassert>
#include "fetch.h"

FetchStage::FetchStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage == NULL);
}

void FetchStage::process() {
  // process for this step
  int cur_pc = getPc();
	Instruction cur_inst = getNextIns();

	cur_pc += 4;
	setPc(cur_pc);
	incStatistics(FETCHEDINS);

	if(cur_inst.getType() == HLT) {
		stopSimulation();
	}
}

FetchStage::~FetchStage() {
}
