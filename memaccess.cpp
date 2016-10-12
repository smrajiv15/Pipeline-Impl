#include <cassert>
#include "memaccess.h"

MemaccessStage::MemaccessStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == EX);
}

void MemaccessStage::process() {
}

MemaccessStage::~MemaccessStage() {
}
