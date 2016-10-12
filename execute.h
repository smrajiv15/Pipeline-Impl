#ifndef EXECUTE_H
#define EXECUTE_H

#include "stage.h"

class ExecuteStage : protected AbstractStage {
  protected:
    ExecuteStage(StageType _type, AbstractStage *_prevStage);
  
  public:
    virtual void process();
    ~ExecuteStage();

    friend class AbstractStage;
};
#endif 
