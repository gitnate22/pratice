#include <iostream>
#include <queue>
#include <stdlib.h>
#include "cube2.hpp"
using std::cout;
using std::string;
using std::cin;
using std::queue;
using std::to_string;

cube2::cube2(){
  bool debug = true;//debug mode switcher
  rubiks =  new int*[6];
  for(int side = 0; side < 6; side++){
    rubiks[side] = new int[4];
    for(int square = 0; square < 4; square++){
      if(!debug){
        cout << getside(side) << " " << getsquare(square) << ": ";
        rubiks[side][square] = getcolor();
      }
      else{
        switch(side){
          case 0:
          rubiks[side][square] = 0; //red
          break;
          case 1:
          rubiks[side][square] = 1; //green
          break;
          case 2:
          rubiks[side][square] = 2; //blue
          break;
          case 3:
          rubiks[side][square] = 4; //white
          break;
          case 4:
          rubiks[side][square] = 3; //yellow
          break;
          case 5:
          rubiks[side][square] = 5; //orange
          break;
        }
      }
    }
  }
}

cube2::~cube2(){
  del(rubiks);
  // for(int side = 0; side < 6; side++){
  //   delete[] rubiks[side];
  // }
  // delete[] rubiks;
}

string cube2::getside(int side){
  switch(side){
    case 0: return "front";
    case 1: return "left";
    case 2: return "right";
    case 3: return "top";
    case 4: return "bottom";
    case 5: return "back";
  }
  return "invalid";
}

string cube2::getsquare(int square){
  switch(square){
    case 0: return "topleft";
    case 1: return "topright";
    case 2: return "bottomleft";
    case 3: return "bottomright";
  }
  return "invalid";
}

int cube2::getcolor(){
  string str;
  int num = -1;
  while(num == -1){
    getline(cin, str);
    if(str == "red" || str == "r")num = 0;
    else if(str == "green" || str == "g")num = 1;
    else if(str == "blue" || str == "b")num = 2;
    else if(str == "yellow" || str == "y")num = 3;
    else if(str == "white" || str == "w")num = 4;
    else if(str == "orange" || str == "o")num = 5;
    else{
        cout << "invalid color, try again: ";
        num = -1;
    }
  }
  return num;
}

string cube2::getcolor(int color){
  switch(color){
    case 0: return "r";
    case 1: return "g";
    case 2: return "b";
    case 3: return "y";
    case 4: return "w";
    case 5: return "o";
  }
  return "i";// + to_string(color);
}

void cube2::print(){
  for(int side = 0; side < 6; side++){
    cout << getside(side) << ":";
    for(int square = 0; square < 4; square++){
      cout << " " << getcolor(rubiks[side][square]);
    }
    cout << "\n";
  }
}

string cube2::gc(int i, int j){
  // cout << i << " " << j << "\n";
  return getcolor(rubiks[i][j]);
}

string cube2::gc(int**instance, int i, int j){
  return getcolor(instance[i][j]);
}

void cube2::printmap(){
  cout << "  " << gc(3,0) << gc(3,1) << "\n";
  cout << "  " << gc(3,2) << gc(3,3) << "\n";
  cout << gc(1,0) << gc(1,1) << gc(0,0) << gc(0,1) << gc(2,0) << gc(2,1) << "\n";
  cout << gc(1,2) << gc(1,3) << gc(0,2) << gc(0,3) << gc(2,2) << gc(2,3) << "\n";
  cout << "  " << gc(4,0) << gc(4,1) << "\n";
  cout << "  " << gc(4,2) << gc(4,3) << "\n";
  cout << "  " << gc(5,0) << gc(5,1) << "\n";
  cout << "  " << gc(5,2) << gc(5,3) << "\n";
}

void cube2::printmap(int**i){
  cout << "  " << gc(i,3,0) << gc(i,3,1) << "\n";
  cout << "  " << gc(i,3,2) << gc(i,3,3) << "\n";
  cout << gc(i,1,0) << gc(i,1,1) << gc(i,0,0) << gc(i,0,1) << gc(i,2,0) << gc(i,2,1) << "\n";
  cout << gc(i,1,2) << gc(i,1,3) << gc(i,0,2) << gc(i,0,3) << gc(i,2,2) << gc(i,2,3) << "\n";
  cout << "  " << gc(i,4,0) << gc(i,4,1) << "\n";
  cout << "  " << gc(i,4,2) << gc(i,4,3) << "\n";
  cout << "  " << gc(i,5,0) << gc(i,5,1) << "\n";
  cout << "  " << gc(i,5,2) << gc(i,5,3) << "\n";
}

void cube2::copy(int**from, int**to){
  for(int side = 0; side < 6; side++){
    for(int square = 0; square < 4; square++){
      to[side][square] = from[side][square];
    }
  }
}

int **cube2::rotate(int**prev, int side, bool clock){
  //make new instance of cube
  int **temp = new int*[6];
  for(int i = 0; i < 6; i++){
    temp[i] = new int[4];
  }
  copy(prev,temp);
  if(clock){ //counter clockwise
    temp[side][0] = prev[side][1];
    temp[side][1] = prev[side][3];
    temp[side][2] = prev[side][0];
    temp[side][3] = prev[side][2];
    switch(side){
      case 0: //front
      temp[3][2] = prev[2][0];
      temp[3][3] = prev[2][2];
      temp[2][0] = prev[4][1];
      temp[2][2] = prev[4][0];
      temp[4][1] = prev[1][3];
      temp[4][0] = prev[1][1];
      temp[1][3] = prev[3][2];
      temp[1][1] = prev[3][3];
      break;
      case 1: //left
      temp[3][0] = prev[0][0];
      temp[3][2] = prev[0][2];
      temp[0][0] = prev[4][0];
      temp[0][2] = prev[4][2];
      temp[4][0] = prev[5][0];
      temp[4][2] = prev[5][2];
      temp[5][0] = prev[3][0];
      temp[5][2] = prev[3][2];
      break;
      case 2: //right
      temp[0][3] = prev[3][3];
      temp[0][1] = prev[3][1];
      temp[3][3] = prev[5][3];
      temp[3][1] = prev[5][1];
      temp[5][3] = prev[4][3];
      temp[5][1] = prev[4][1];
      temp[4][3] = prev[0][3];
      temp[4][1] = prev[0][1];
      break;
      case 3: //top
      temp[5][2] = prev[2][1];
      temp[5][3] = prev[2][0];
      temp[2][1] = prev[0][1];
      temp[2][0] = prev[0][0];
      temp[0][1] = prev[1][1];
      temp[0][0] = prev[1][0];
      temp[1][1] = prev[5][2];
      temp[1][0] = prev[5][3];
      break;
      case 4: //bottom
      temp[0][2] = prev[2][2];
      temp[0][3] = prev[2][3];
      temp[2][2] = prev[5][1];
      temp[2][3] = prev[5][0];
      temp[5][1] = prev[1][2];
      temp[5][0] = prev[1][3];
      temp[1][2] = prev[0][2];
      temp[1][3] = prev[0][3];
      break;
      case 5: //back
      temp[4][2] = prev[2][3];
      temp[4][3] = prev[2][1];
      temp[2][3] = prev[3][1];
      temp[2][1] = prev[3][0];
      temp[3][1] = prev[1][0];
      temp[3][0] = prev[1][2];
      temp[1][0] = prev[4][2];
      temp[1][2] = prev[4][3];
      break;
    }
  }else{ //clockwise
    temp[side][0] = prev[side][2];
    temp[side][1] = prev[side][0];
    temp[side][2] = prev[side][3];
    temp[side][3] = prev[side][1];
    switch(side){
      case 0://front
      temp[3][2] = prev[1][3];
      temp[3][3] = prev[1][1];
      temp[1][3] = prev[4][1];
      temp[1][1] = prev[4][0];
      temp[4][1] = prev[2][0];
      temp[4][0] = prev[2][2];
      temp[2][0] = prev[3][2];
      temp[2][2] = prev[3][3];
      break;
      case 1: //left
      temp[3][0] = prev[5][0];
      temp[3][2] = prev[5][2];
      temp[5][0] = prev[4][0];
      temp[5][2] = prev[4][2];
      temp[4][0] = prev[0][0];
      temp[4][2] = prev[0][2];
      temp[0][0] = prev[3][0];
      temp[0][2] = prev[3][2];
      break;
      case 2: //right
      temp[3][3] = prev[0][3];
      temp[3][1] = prev[0][1];
      temp[0][3] = prev[4][3];
      temp[0][1] = prev[4][1];
      temp[4][3] = prev[5][3];
      temp[4][1] = prev[5][1];
      temp[5][3] = prev[3][3];
      temp[5][1] = prev[3][1];
      break;
      case 3: //top
      temp[5][2] = prev[1][1];
      temp[5][3] = prev[1][0];
      temp[1][1] = prev[0][1];
      temp[1][0] = prev[0][0];
      temp[0][1] = prev[2][1];
      temp[0][0] = prev[2][0];
      temp[2][1] = prev[5][2];
      temp[2][0] = prev[5][3];
      break;
      case 4: //bottom
      temp[0][2] = prev[1][2];
      temp[0][3] = prev[1][3];
      temp[1][2] = prev[5][1];
      temp[1][3] = prev[5][0];
      temp[5][1] = prev[2][2];
      temp[5][0] = prev[2][3];
      temp[2][2] = prev[0][2];
      temp[2][3] = prev[0][3];
      break;
      case 5: //back
      temp[4][2] = prev[1][0];
      temp[4][3] = prev[1][2];
      temp[1][0] = prev[3][1];
      temp[1][2] = prev[3][0];
      temp[3][1] = prev[2][3];
      temp[3][0] = prev[2][1];
      temp[2][3] = prev[4][2];
      temp[2][1] = prev[4][3];
      break;
    }
  }
  return temp;
}

void cube2::solve(){
  bool debug = false;
  if(debug){
    cout << "rubricks\n";
    printmap();
    int** current = rotate(rubiks, 0, 0);
    cout << "current after roation\n";
    printmap(current);
    cout << (check(current) ? "true" : "false") << "\n";
    del(current);
  } else {
    //make a current variable to hold
    int**current;
    int**temp;
    queue<int**> q;
    q.push(rubiks);
    int count = 0;
    bool found = check(q.front());
    //uses BFS to find the solved cube
    while(!found){
      count++;
      current = q.front();
      q.pop();
      for(int side = 0; side < 6; side++){
        temp = rotate(current,side,0);
        if(check(temp)){
          found = true;
        }
        q.push(temp);
        temp = rotate(current,side,1);
        if(check(temp)){
          found = true;
        }
        q.push(temp);
      }
      if(current != rubiks){
        del(current);
      }
    }
    cout << count << " found the solution\n";
    //delete everything in the queue
    while(!q.empty()){
      del(q.front());
      q.pop();
    }
  }
}

void cube2::del(int**instance){
  // cout << "here1\n";
  for(int side = 0; side < 6; side++){
    delete[] instance[side];
  }
  // cout << "here2\n";
  delete[] instance;
  instance = NULL;
  // cout << "here3\n";
}

bool cube2::check(int**instance){
  int temp;
  for(int side = 0; side < 6; side++){
    temp = instance[side][1];
    for(int square = 1; square < 4; square++){
      if(temp != instance[side][square]){
        return false;
      }
    }
  }
  return true;
}

void cube2::scramble(){
  // srand(time(NULL)); //make it random
  bool debug = true;
  cout << "scrambling\n";
  if(debug){
    rot(0,0);
    // rot(3,1);
  }else{
    int side;
    bool clock;
    for(int rep = 10+rand()%10; rep>0; rep--){
      side = rand()%6;
      clock = rand()%2;
      cout << "rotating " << getside(side) << " " << (clock ? "counter-" : "") << "clockwise\n";
      rot(side,clock);
    }
  }
}

void cube2::rot(int side, bool clock){
  int **temp;
  temp = rotate(rubiks,side,clock);
  del(rubiks);
  rubiks = temp;
  temp = NULL;
}
