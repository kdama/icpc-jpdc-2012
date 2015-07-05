#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

const int MIN_DICEFACE  = 1;
const int MAX_DICEFACE  = 6;
const int DROPPABLE_MIN = 4;               // as given.
const int MAX_N         = 100;             // as given.
const int MAP_WIDTH     = MAX_N * 2 + 1;   // dice can roll N times in 4 directions.
const int MAP_HEIGHT    = MAX_N * 2 + 1;   // dice can roll N times in 4 directions.
const int DROP_AT_X     = MAP_WIDTH / 2;   // center of map.
const int DROP_AT_Y     = MAP_HEIGHT / 2;  // center of map.
const int DIRECTION_X[] = { -1, 1,  0, 0}; // left, right, bottom, top
const int DIRECTION_Y[] = {  0, 0, -1, 1}; // left, right, bottom, top
const int NUM_DIRECTION = sizeof(DIRECTION_X) / sizeof(DIRECTION_X[0]);

typedef int Grid[MAP_WIDTH][MAP_HEIGHT];

void init(Grid top_grid, Grid height_grid, int face_count[MAX_DICEFACE + 1]) {
  for (int x = 0; x < MAP_WIDTH; x++) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      top_grid[x][y] = height_grid[x][y] = 0;
    }
  }
  for (int i = 0; i <= MAX_DICEFACE; i++) {
    face_count[i] = 0;
  }
}

int opposite(int face) {
  return MAX_DICEFACE + MIN_DICEFACE - face;
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
  if (top >= 4) return third_side(opposite(top), opposite(front));
}

void drop(int top, int front, int x, int y,
          Grid top_grid, Grid height_grid) {
  int sides[NUM_DIRECTION];
  for (int i = 0; i < NUM_DIRECTION; i++) {
    if (height_grid[x][y] > height_grid[x + DIRECTION_X[i]][y + DIRECTION_Y[i]]) {
      if (i == 0) sides[i] = front;
      else if (i == 1) sides[i] = opposite(front);
      else if (i == 2) sides[i] = opposite(third_side(top, front));
      else if (i == 3) sides[i] = third_side(top, front);
    }
    else sides[i] = 0;
  }
  sort(sides, sides + NUM_DIRECTION);
  if (sides[NUM_DIRECTION - 1] < DROPPABLE_MIN) {
    // finish dropping
    top_grid[x][y] = top;
    height_grid[x][y]++;
  } else {
    int direction, next_front;
    if (sides[NUM_DIRECTION - 1] == front) {
      direction = 0;
      next_front = top;
    } else if (sides[NUM_DIRECTION - 1] == opposite(front)) {
      direction = 1;
      next_front = opposite(top);
    } else if (sides[NUM_DIRECTION - 1] == opposite(third_side(top, front))) {
      direction = 2;
      next_front = front;
    } else if (sides[NUM_DIRECTION - 1] == third_side(top, front)) {
      direction = 3;
      next_front = front;
    }
    drop(opposite(sides[NUM_DIRECTION - 1]), next_front,
         x + DIRECTION_X[direction], y + DIRECTION_Y[direction], top_grid, height_grid);
  }
}

int main(int argc, char* argv[]) {
  while (1) {
    int N;
    int top[MAX_N], front[MAX_N];           // top-face & front-face of i-th dice.
    Grid top_grid;                    // top-face map. 0 means no dice.
    Grid height_grid;                 // height; number of dice at (x, y).
    int face_count[MAX_DICEFACE + 1]; // use face_count[1] .. face_count[6].

	cin >> N;
	if (N == 0) break;
    
    init(top_grid, height_grid, face_count);
    
    for (int i = 0; i < N; i++) {
      cin >> top[i] >> front[i];
      drop(top[i], front[i], DROP_AT_X, DROP_AT_Y, top_grid, height_grid);
    }
    
    for (int x = 0; x < MAP_WIDTH; x++) {
      for (int y = 0; y < MAP_HEIGHT; y++) {
        face_count[top_grid[x][y]]++;
      }
    }
    
    for (int i = MIN_DICEFACE; i <= MAX_DICEFACE; i++) {
      cout << face_count[i];
      if (i == MAX_DICEFACE) cout << endl;
      else cout << " ";
    }
  }
  return 0;
}

/*
VERSION 01 17:23-18:30 http://ideone.com/4t13O2
VERSION 02 http://ideone.com/wqy5p0
*/
