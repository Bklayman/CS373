#ifndef STATE_HH_
#define STATE_HH_

#include <list>

#include "transition.hh"

class State {
private:
  int index;
  int stateType;
  std::list<Transition> transitions;

public:
  State(int curIndex, int curStateType){
    index = curIndex;
    stateType = curStateType;
  }

  int getIndex(){
    return index;
  }

  int getStateType(){
    return stateType;
  }

};

#endif
