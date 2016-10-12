#include <cassert>
#include "stage.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "memaccess.h"
#include "writeback.h"

AbstractStage::getPcPtr AbstractStage::getPc = NULL;
AbstractStage::setPcPtr AbstractStage::setPc = NULL;
AbstractStage::getNextInsPtr AbstractStage::getNextIns = NULL;
AbstractStage::getRegPtr AbstractStage::getReg = NULL;
AbstractStage::setRegPtr AbstractStage::setReg = NULL;
AbstractStage::getDataPtr AbstractStage::getData = NULL;
AbstractStage::setDataPtr AbstractStage::setData = NULL;
AbstractStage::setStopSimulationPtr AbstractStage::stopSimulation = NULL;
AbstractStage::getCyclePtr AbstractStage::getCycle = NULL;
AbstractStage::incStatisticsPtr AbstractStage::incStatistics = NULL;


AbstractStage::AbstractStage(StageType _type, AbstractStage *_prevStage) : stalled(false), type(_type), 
                                                                         prevStage(_prevStage) {
  if (prevStage != NULL) {
    prevStage->nextStage = this;
	}

  nextStage = NULL;
}

AbstractStage* AbstractStage::createStage(StageType _type, AbstractStage *_prevStage) {

  	AbstractStage *stage = NULL;

  	if(_type == IF) {
			stage = new FetchStage(_type, _prevStage);
		} else if(_type == ID) {
			stage = new DecodeStage(_type, _prevStage);
		} else if(_type == EX) {
			stage = new ExecuteStage(_type, _prevStage);
		} else if(_type == MEM) {
			stage = new MemaccessStage(_type, _prevStage);
		} else if(_type == WR) {	
			stage = new WritebackStage(_type, _prevStage);
		} 
    return stage;
}

void AbstractStage::setStalled() {
  stalled = true; 
  if (prevStage)
    prevStage->setStalled();
}

void AbstractStage::setUnstalled() { 
  stalled = false; 
  if (prevStage)
    prevStage->setUnstalled();
}

void AbstractStage::updateDependences(int _srcCycle) {
  // This function is used to notify (and possibly unstall) the consumer instruction that was stalled
  // due to the current instruction (i.e., producer instruction) of this stage
}

void AbstractStage::setInstruction(Instruction& _ins) {
  ins = _ins;
}

Instruction& AbstractStage::getInstruction() {
  return ins;
}

AbstractStage::~AbstractStage() {
}
