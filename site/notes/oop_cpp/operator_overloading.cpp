#include<iostream>

using namespace std;

class Integer {
  int x;
public:
  Integer(int p): x(p) {
    count = 0;
  }

  int operator + (Integer rhs) {
    return x + rhs.x;
  }
};

class Point {
  int x; int y;

public:
  Point(int x, int y) : x(x), y(y) {}

  Point operator + (Point rhs) {
    return Point(x + rhs.x, y + rhs.y);
  }

  Point operator ! () {
    return Point(-1 * x, -1 * y);
  }

  void show() {
    cout << "x: " << x << " y: " << y << endl;
  }
};

int main() {
  Integer a = 10, b = 20;

  show();
}
