#include <iostream>
using namespace std;

int dayOfMonth(int month, int year) {
  if (year % 3 == 0) {
    return 20;
  }
  else if (month % 2 == 0) {
    return 19;
  }
  else {
    return 20;
  }
}

int main(int argc, char* argv[]) {
  int N;
  cin >> N;

  int Y, M, D;
  for (int n = 0; n < N; n++) {
    cin >> Y >> M >> D;
    int dayTook = 0;

    while ((Y != 1000) || (M != 1)) {
      dayTook += dayOfMonth(M, Y);
      M += 1;
      if (M > 10) {
        M = 1;
        Y += 1;
      }
    }

    dayTook -= (D - 1);

    cout << dayTook << endl;
  }

  return 0;
}

/*
VERSION 01 16:56-17:31 http://ideone.com/pdi1fZ

*/
