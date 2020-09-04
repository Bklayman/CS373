#ifndef TRANSITION_HH_
#define TRANSITION_HH_

class Transition {
private:
  int target;
  char symbol;
  char overwrite;
  char move;

public:
  Transition(int curTarget, char curSymbol, char curOverwrite, char curMove){
    target = curTarget;
    symbol = curSymbol;
    overwrite = curOverwrite;
    move = curMove;
  }

  int getTarget(){
    return target;
  }

  char getSymbol(){
    return symbol;
  }

  char getOverwrite(){
    return overwrite;
  }

  char getMove(){
    return move;
  }

};

#endif
