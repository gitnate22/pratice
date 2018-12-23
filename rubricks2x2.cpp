#include <iostream>
using std::cout;

#include "cube2.hpp"

int main(){
  cube2 game;
  // game.print();
  game.printmap();
  game.scramble();
  game.printmap();
  game.solve();
  game.printmap();
  return 0;
}
