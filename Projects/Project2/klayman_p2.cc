#include <cstring>
#include <iostream>

char* changeCenterToggle(char curToggleStates[], char ballState){
  if(ballState == '0'){
    if(curToggleStates[0] == 'L'){
      curToggleStates[0] = 'R';
    } else if(curToggleStates[0] == 'R'){
      curToggleStates[0] = 'C';
    } else{
      curToggleStates[0] = 'L';
    }
  } else {
    if(curToggleStates[0] == 'L'){
      curToggleStates[0] = 'C';
    } else if(curToggleStates[0] == 'R'){
      curToggleStates[0] = 'L';
    } else{
      curToggleStates[0] = 'R';
    }
  }
  return curToggleStates;
}

void traceBallGame(char* toggleConfig, char* ballStates) {
  char curToggleStates[4];
  for(int i = 0; i < 4; i++){
    curToggleStates[i] = toggleConfig[i];
  }
  for(int i = 0; i < 4; i++){
    std::cout << curToggleStates[i];
  }
  char lastExit = 'F';
  for(int i = 0; ballStates[i] != '\0'; i++) {
    if(curToggleStates[0] == 'L'){
      strcpy(curToggleStates, changeCenterToggle(curToggleStates, ballStates[i]));
      if(curToggleStates[1] == 'L'){
        curToggleStates[1] = 'R';
        lastExit = 'B';
      } else {
        curToggleStates[1] = 'L';
        lastExit = 'C';
      }
    } else if(curToggleStates[0] == 'C') {
      strcpy(curToggleStates, changeCenterToggle(curToggleStates, ballStates[i]));
      if(curToggleStates[2] == 'L'){
        curToggleStates[2] = 'R';
        lastExit = 'C';
      } else {
        curToggleStates[2] = 'L';
        lastExit = 'D';
      }
    } else {
      strcpy(curToggleStates, changeCenterToggle(curToggleStates, ballStates[i]));
      if(curToggleStates[3] == 'L'){
        curToggleStates[3] = 'R';
        lastExit = 'D';
      } else {
        curToggleStates[3] = 'L';
        lastExit = 'E';
      }
    }
    std::cout << "->";
    for(int i = 0; i < 4; i++){
      std::cout << curToggleStates[i];
    }
  }
  std::cout << " " << lastExit << std::endl;
}

int main(int argc, char* argv[]) {
  if(argc != 3) {
    std::cout << "Usage: ./klayman_p2 <toggle configuration> <ball states>" << std::endl;
    exit(1);
  }
  traceBallGame(argv[1], argv[2]);
  return 1;
}
