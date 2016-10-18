#include <cassert>
#include "fetch.h"

FetchStage::FetchStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage == NULL);
}

void FetchStage::process() {
  // process for this step
  int cur_pc = getPc();
	
	setInstruction(getNextIns());
	getInstruction().setFetchedAtCycle(getCycle());		
	cur_pc += 4;
	setPc(cur_pc);
	incStatistics(FETCHEDINS);
}

FetchStage::~FetchStage() {
}
