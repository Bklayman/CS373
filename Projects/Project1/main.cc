#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "state.hh"
#include "transition.hh"

// void printList(std::list<std::string> listStr){
//   std::cout << "PrintedList: " << std::endl;
//   for(std::list<std::string>::iterator listIt = listStr.begin(); listIt != listStr.end(); ++listIt){
//     std::cout << *listIt << std::endl;
//   }
//   std::cout << std::endl;
// }

// void printList(std::list<State*> listState){
//   std::cout << "Printed List: " << std::endl;
//   for(std::list<State*>::iterator stateIt = listState.begin(); stateIt != listState.end(); ++stateIt){
//     std::cout << (*stateIt)->getIndex() << std::endl;
//   }
//   std::cout << std::endl;
// }

void printStates(std::list<State*> states){
  for(std::list<State*>::iterator stateIt = states.begin(); stateIt == states.end(); ++stateIt){
    State* curState = *stateIt;
    std::cout << curState->getIndex() << std::endl;
  }
}

char stringToChar(std::string originalString){
  if(originalString.size() != 1){
    std::cout << "Error: " << originalString << " has more than one character." << std::endl;
    exit(1);
  }
  return originalString.at(0);
}

int stringToInt(std::string originalString){
  int result;
  try{
    result = std::stoi(originalString);
  } catch(...){
    std::cout << "Error: " << originalString << " is not an integer." << std::endl;
    exit(1);
  }
  return result;
}

std::list<std::string> splitString(std::string input){ //Does not work
  std::list<std::string> result;
  std::string word = "";
  for(auto inputChar : input){
    if((int)inputChar == 32 || (int)inputChar == 9){
      result.push_back(word);
      word = "";
    } else {
      word += inputChar;
    }
  }
  result.push_back(word);
  return result;
}

std::list<State*> createFiniteAutomata(char* fileName){
  std::fstream file;
  file.open(fileName);
  if(!file.is_open()){
    std::cout << "Error: File is unable to open." << std::endl;
    exit(1);
  }
  bool startExists = false;
  bool transitions = false;
  std::list<State*> results;
  std::string lineRead;
  while(std::getline(file, lineRead)){
    std::list<std::string> tokens = splitString(lineRead);
    std::list<std::string>::iterator tokenIt = tokens.begin();
    if(transitions || *tokenIt == "transition"){
      if(!startExists){
        std::cout << "Error: FA does not have a start state." << std::endl;
        exit(1);
      }
      transitions = true;
      ++tokenIt;
      int fromIndex = stringToInt(*tokenIt);
      ++tokenIt;
      char charAccept = stringToChar(*tokenIt);
      ++tokenIt;
      int toIndex = stringToInt(*tokenIt);
      ++tokenIt;
      char charReplace = stringToChar(*tokenIt);
      ++tokenIt;
      char moveChar = stringToChar(*tokenIt);
      State* curState = nullptr;
      bool stateFound = false;
      for(std::list<State*>::iterator stateIt = results.begin(); stateIt != results.end(); ++stateIt){
        if((*stateIt)->getIndex() == fromIndex){
          curState = (*stateIt);
          stateFound = true;
          break;
        }
      }
      Transition curTransition = Transition(toIndex, charAccept, charReplace, moveChar);
      if(stateFound){
        curState->addTransition(curTransition);
      } else {
        curState = new State(fromIndex, 3);
        curState->addTransition(curTransition);
        results.push_back(curState);
      }
    } else {
      ++tokenIt;
      std::string stateIndexStr = *tokenIt;
      ++tokenIt;
      std::string stateType = *tokenIt;
      int stateIndex = stringToInt(stateIndexStr);
      int typeIndex = -1;
      if(stateType == "start"){
        if(startExists){
          std::cout << "Error: Multiple start states found." << std::endl;
        }
        typeIndex = 0;
        startExists = true;
      } else if(stateType == "accept") {
        typeIndex = 1;
      } else if(stateType == "reject") {
        typeIndex = 2;
      } else if(stateType == "null") {
        typeIndex = 3;
      } else {
        std::cout << "Error: Invalid state type given." << std::endl;
        exit(1);
      }
      State* curState = new State(stateIndex, typeIndex);
      results.push_back(curState);
    }
  }
  return results;
}

int main(int argc, char* argv[]){
  if(argc != 3){
    std::cout << "Usage: ./klayman_p1 <text file defining FA> <string to run through defined FA>" << std::endl;
    exit(1);
  }

  std::list<State*> finiteAutomata = createFiniteAutomata(argv[1]);

}
