#ifndef DECODE_H
#define DECODE_H

#include "stage.h"

class DecodeStage : protected AbstractStage {
  protected:
    DecodeStage(StageType _type, AbstractStage *_prevStage);
  
  public:
    virtual void process();
    ~DecodeStage();

    friend class AbstractStage;
};
#endif 
