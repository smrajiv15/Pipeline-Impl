#include <cassert>
#include "decode.h"

#include<typeinfo>

DecodeStage::DecodeStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == IF);
}

void DecodeStage::process() {
}

DecodeStage::~DecodeStage() {
}
