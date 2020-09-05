#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "state.hh"
#include "transition.hh"

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

std::list<std::string> splitString(std::string input){
  std::list<std::string> result;
  int spaceLocation = input.find(" ");
  while(spaceLocation != -1){
    std::string token = input.substr(0, spaceLocation);
    result.push_back(token);
    input = input.substr(spaceLocation + 1, input.size() - spaceLocation - 1);
    spaceLocation = input.find(" ");
  }
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
        typeIndex = 0;
      } else if(stateType == "accept") {
        typeIndex = 1;
      } else if(stateType == "reject") {
        typeIndex = 2;
      } else if(stateType == "null") {
        typeIndex = 3;
      } else {
        std::cout << "Error: Invalid state type given." << std::endl;
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
