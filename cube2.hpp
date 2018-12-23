#include <string>
using std::string;


class cube2{
public:
  cube2();
  ~cube2();
  int getcolor();
  void print();
  void printmap();
  void solve();
  void scramble();
private:
  int**rubiks;
  void rot(int side, bool clock);
  int** rotate(int **prev, int side, bool clock);
  string getside(int side);
  string getsquare(int square);
  string getcolor(int color);
  string gc(int i, int j);
  string gc(int**instance, int i, int j);
  bool check(int**instance);
  void copy(int**from, int**to);
  void del(int** instance);
  void printmap(int**i);
  struct path{
    path(){
      cube = NULL;
      side = -1;
      clock = 0;
      previous = NULL;
    }
    path(int s, int cl, int**cu, path*p){
      cube = cu;
      side = s;
      clock = cl;
      previous = p;
    }
    int **cube;
    int side;
    int clock;
    path *previous;
  };
};

/*
side:
0 - front
1 - left
2 - right
3 - top
4 - bottom
5 - back
square:
0 - topleft
1 - topright
2 - bottomleft
3 - bottomright
clock:
0 - clockwise
1 - coutner clockwise
color:
0 - red
1 - green
2 - blue
3 - yellow
4 - white
5 - orange
*/
