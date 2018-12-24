#include <iostream>
using std::cout;

#include "cube2.hpp"

int main(){
  cube2 game;
  // game.print();
  game.printmap();
  cout << game.sgetcheck() << "\n";
  game.scramble();
  // game.printmap();
  // cout << game.sgetcheck() << "\n";
  cout << "---------------------------\n";
  game.solve();
  // game.print();
  // game.printmap();
  // cout << game.sgetcheck() << "\n";
  return 0;
}
