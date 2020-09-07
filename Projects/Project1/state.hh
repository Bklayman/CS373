#ifndef STATE_HH_
#define STATE_HH_

#include <list>

#include "transition.hh"

class State {
private:
  int index;
  int stateType; //0 = start, 1 = accept, 2 = reject, 3 = null
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

  void setStateType(int setType){
    stateType = setType;
  }

  std::list<Transition> getTransitions(){
    return transitions;
  }

  void addTransition(Transition connection){
    transitions.push_back(connection);
  }

};

#endif
