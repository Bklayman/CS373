#include <fstream>
#include <iostream>
#include <list>

#include "state.hh"
#include "transition.hh"

std::list<State> createFiniteAutomata(char* fileName){
  std::fstream file;
  file.open(fileName);
  if(!file.is_open()){
    std::cout << "Error: File is unable to open." << std::endl;
    exit(1);
  }
}

int main(int argc, char* argv[]){
  if(argc != 3){
    std::cout << "Usage: ./klayman_p1 <text file defining FA> <string to run through defined FA>" << std::endl;
    exit(1);
  }

  std::list<State> finiteAutomata = createFiniteAutomata(argv[1]);
}
