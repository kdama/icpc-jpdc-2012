#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int N;
int t[100];
int f[100];
int tops[201][201];
int height[201][201];
int cnt[7];
int SIDE_X[] = { -1, 1,  0, 0};
int SIDE_Y[] = {  0, 0, -1, 1};

void init() {
  for (int i = 0; i < 201; i++) {
    for (int j = 0; j < 201; j++) {
      tops[i][j] = height[i][j] = 0;
    }
  }
  for (int i = 0; i < 7; i++) {
    cnt[i] = 0;
  }
}

int third_side(int top, int front) {
  if (top == 1) {
    if (front == 2) return 3;
    if (front == 3) return 5;
    if (front == 5) return 4;
    if (front == 4) return 2;
  }
  if (top == 2) {
    if (front == 1) return 4;
    if (front == 4) return 6;
    if (front == 6) return 3;
    if (front == 3) return 1;
  }
  if (top == 3) {
    if (front == 5) return 1;
    if (front == 1) return 2;
    if (front == 2) return 6;
    if (front == 6) return 5;
  }
  if (top >= 4) return third_side(7 - top, 7 - front);
}

void drop(int top, int front, int x, int y) {
  int sides[4];
  for (int i = 0; i < 4; i++) {
    if (height[x][y] > height[x + SIDE_X[i]][y + SIDE_Y[i]]) {
      if (i == 0) sides[i] = front;
      else if (i == 1) sides[i] = 7 - front;
      else if (i == 2) sides[i] = 7 - third_side(top, front);
      else if (i == 3) sides[i] = third_side(top, front);
    }
    else sides[i] = 0;
  }
  sort(sides, sides + 4);
  if (sides[3] <= 3) {
    // finish dropping
    tops[x][y] = top;
    height[x][y]++;
  }
  else {
    int direction, next_front;
    if (sides[3] == front) {
      direction = 0;
      next_front = top;
    } else if (sides[3] == 7 - front) {
      direction = 1;
      next_front = 7 - top;
    } else if (sides[3] == 7 - third_side(top, front)) {
      direction = 2;
      next_front = front;
    }
    else if (sides[3] == third_side(top, front)) {
      direction = 3;
      next_front = front;
    }
    drop(7 - sides[3], next_front, x + SIDE_X[direction], y + SIDE_Y[direction]);
  }
}

int main(int argc, char* argv[]) {
  while (1) {
    cin >> N;
    if (N == 0) break;
    init();
    for (int i = 0; i < N; i++) {
      cin >> t[i] >> f[i];
      drop(t[i], f[i], 100, 100);
    }
    for (int i = 0; i < 201; i++) {
      for (int j = 0; j < 201; j++) {
        cnt[tops[i][j]]++;
      }
    }
    for (int i = 1; i <= 6; i++) {
      cout << cnt[i];
      if (i == 6) cout << endl;
      else cout << " ";
    }
  }
  return 0;
}

/*
VERSION 01 17:23-18:30 http://ideone.com/4t13O2

*/
